#include "game.hh"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <map>

void Game::ghost_transition_phase(Ghost &ghost) {
	sf::Vector2f screen_displacement, src_screen_pos, dst_screen_pos;
	src_screen_pos = ghost.get_screen_float_coordinate();
	dst_screen_pos = _map.get_screen_float_coordinate(ghost.get_cur_pos());

	// Arrived at the intended block.
	if(std::fabs(src_screen_pos.x - dst_screen_pos.x) <= ghost.get_speed() * 1.5f && std::fabs(src_screen_pos.y - dst_screen_pos.y) <= ghost.get_speed() * 1.5f) { 
		// Calibrate the position on screen.
		ghost.set_screen_coordinate(_map.get_screen_coordinate(ghost.get_map_coordinate()));
		// Guide the ghost to the next block.
    	ghost.next();	
		ghost.set_map_coordinate(_map.get_map_coordinate(ghost.get_cur_pos()));
		
	}
	else {
		// Warp if the departing block and the arrival block are gateways.
		if(ghost.get_prev_pos() != ghost.get_cur_pos() && _map(ghost.get_cur_pos()).is_gateway() && _map(ghost.get_prev_pos()).is_gateway()) {
			ghost.set_screen_coordinate(_map.get_screen_coordinate(ghost.get_cur_pos()));
			return;
		}
		// Move slowly to the next block.
		screen_displacement = dst_screen_pos - src_screen_pos;
		screen_displacement.x = ghost.get_speed() * (std::fabs(screen_displacement.x) < 0.1f ? 0 : (screen_displacement.x < 0 ? -1 : 1));
		screen_displacement.y = ghost.get_speed() * (std::fabs(screen_displacement.y) < 0.1f ? 0 : (screen_displacement.y < 0 ? -1 : 1));
		ghost.set_screen_float_coordinate(src_screen_pos + screen_displacement);
	}
}
void Game::random_destination(Ghost &ghost) {
	sf::Vector2i cur_pos = ghost.get_map_coordinate(), arrival;
    
	
	bool arrived = true, again = false;
    int i = 0;

    if (_map(cur_pos).is_intersection()) {
		// If there is a path but the ghost hasn't arrived yet, don't set the arrive flag.
        if (ghost.get_path().size() > 0 && cur_pos != ghost.get_path().back())
                arrived = false;
		// If arrive flag is set, set the new path for the ghost 
        if (arrived) {
            do {
				again = false;
				//Choose a random destination
                i = std::rand() % _map._cst_vertices.size();
                arrival = _map._cst_vertices[i].get_vertex_block().get_map_coordinate();
				//Avoid ghost house
                for (i = 0; i < _map.get_house_index_end(); i++) {
                    if (arrival == _map.ghost_house_at(i))
                        again = true;
                }
            } while (arrival == cur_pos || again); // Rechoose if arrival point is depart point / ghost house.
            ghost.set_path(_map.shortest_route(cur_pos, arrival));
        }
    }
	ghost_transition_phase(ghost);
}
void Game::chase(Ghost &ghost, Creature &creature, bool ambush) {
	//Ambush mode chooses the second closest intersection to the pacman.
	sf::Vector2i cur_pos = ghost.get_map_coordinate();
	// Routing is done at each intersection in order to keep up with pacman.
	if(_map(cur_pos).is_intersection()) {
			// Choose the closest intersection.
		sf::Vector2i target_intersection = arriving_intersection_of(creature, !ambush);
		if(cur_pos != target_intersection) {
			ghost.set_path(_map.shortest_route(cur_pos, target_intersection));
		}
		else {
			// The closest intersection is reached. traverse the edge at which the pacman is.
			target_intersection = arriving_intersection_of(creature, ambush);
			if(target_intersection != cur_pos) {
				ghost.set_path(_map.specified_route(cur_pos, target_intersection));
			}
		}			
	}
	ghost_transition_phase(ghost);
}
void Game::patrol(Ghost &ghost) {
	// Patroling is revolves around blinky.
	// It is similar to ambushing blinky.
	chase(ghost, _blinky, true);
}
/*
void Game::scatter(Ghost &ghost, sf::Vector2i &arrival_pos) {

}*/
// Inkey, Clyde, Pinky move back and forth until the game starts.
bool Game::back_and_forth(Ghost &ghost) { /*
	int i = 0, begin, end;
	bool *is_reversed;
	
	if(ghost.get_entity_id() == Entity::EntityID::Pinky) {
		i = Map::House::Pinky;
		begin = _map.get_house_index_pinky();
		end = _map.get_house_index_inkey() - 1;
		is_reversed = &_pinky_reversed;
	}
	else if(ghost.get_entity_id() == Entity::EntityID::Clyde) {
		i = Map::House::Clyde;
		begin = _map.get_house_index_clyde();
		end = _map.get_house_index_end() - 1;
		is_reversed = &_clyde_reversed;
	}
	else if(ghost.get_entity_id() == Entity::EntityID::Inkey) {
		i = Map::House::Inkey;
		begin = _map.get_house_index_inkey();
		end = _map.get_house_index_clyde() - 1;
		is_reversed = &_inkey_reversed;
	}

	if (_house_index[i] == begin) 
		*is_reversed = false; 
	else if (_house_index[i] == end) 
		*is_reversed = begin;

	_house_index[i] += (*is_reversed ? -1 : 1);*/
	return true;	
}

sf::Vector2i Game::arriving_intersection_of(const Creature &creature,bool closest) {
	sf::Vector2i creature_pos, v1, v2;

	creature_pos = creature.get_map_coordinate();

	// Find the edge at which the pacman is.
	for(const auto& edge_iter : _map._cst_edges) {
		// v1: beginning intersection / v2: ending intersection.
		v1 = edge_iter.get_vertices().front()->get_map_coordinate();
		v2 = edge_iter.get_vertices().back()->get_map_coordinate();

		// Return immediately the closest or second closest intersection.
		if (v1 == creature_pos) 
			return (closest ? v1 : v2);
		if (v2 == creature_pos)
			return (closest ? v2 : v1);

		for(const auto& block_iter : edge_iter.get_route()) {
			if(block_iter->get_map_coordinate() == creature_pos) {
				// Compare the distance bewteen first intersection and second intersection between which the pacman is.
				// Return the closest or second closest intersection.
				if(std::hypot((v1 - creature_pos).x, (v1 - creature_pos).y) <= std::hypot((v2 - creature_pos).x, (v2 - creature_pos).y))
					return  (closest ? v1 : v2);
				else 
					return  (closest ? v2 : v1);
				
			}
		}
	}
	return sf::Vector2i(0,0);
}