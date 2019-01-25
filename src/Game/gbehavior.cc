#include "game.hh"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
void Game::random_destination(Ghost &ghost, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos = ghost.get_map_coordinate(), arrival;
    
	if(!is_pacman_moved || arrival_pos != cur_pos)
		return;
	bool arrived = true, again = false;
    int i = 0;

    if (_map(cur_pos).is_intersection()) {
        if (ghost.get_path().size() > 0) {
            if (cur_pos != ghost.get_path().back())
                arrived = false;
        }

        if (arrived) {
            do {
                i = std::rand() % _map._cst_vertices.size();
                arrival = _map._cst_vertices[i].get_vertex_block().get_map_coordinate();
                if (arrival != cur_pos)
                    again = false;
                for (i = 0; i < _map.get_house_index_end() - 1; i++) {
                    if (arrival == _map.ghost_house_at(i))
                        again = true;
                }
            } while (again);

            std::vector<struct Vertex::Path> &spaths = _map.shortest_route(_map(cur_pos), _map(arrival));
			
            ghost.set_path(spaths);
        }
    }

    sf::Vector2i displacement = ghost.get_cur_pos();
    ghost.next();
    displacement = ghost.get_cur_pos() - displacement;
	move_creature(ghost, displacement, arrival_pos);
}
void Game::patrol(Ghost &ghost, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos = ghost.get_map_coordinate();
    if(!is_pacman_moved && cur_pos == arrival_pos)
		return;
	if(_map(cur_pos).is_intersection() && cur_pos == arrival_pos) {
        for(auto const &iter : _map._cst_vertices) {
            if(iter.get_vertex_block().get_map_coordinate() == cur_pos){
                sf::Vector2i target_intersection = arriving_intersection_of(_blinky, false);
                if(cur_pos != target_intersection) {
                    std::vector<struct Vertex::Path> &spaths = _map.shortest_route(iter.get_vertex_block(), _map(target_intersection));
                    ghost.set_path(spaths);
                }
                else {
                    target_intersection = arriving_intersection_of(_blinky, true);
                    if(target_intersection != cur_pos) {
                        std::vector<struct Vertex::Path> &spaths = _map.specified_route(iter.get_vertex_block(), _map(target_intersection));
                        ghost.set_path(spaths);
                    }
                }
            }
        }
    }
	sf::Vector2i displacement = ghost.get_cur_pos();
	ghost.next();
	displacement = ghost.get_cur_pos() - displacement;
	//std::cerr<<displacement.x << " " << displacement.y<< std::endl;
	move_creature(ghost, displacement, arrival_pos);
}
void Game::scatter(Ghost &ghost, sf::Vector2i &arrival_pos) {

}
bool Game::back_and_forth(Ghost &ghost) {
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

	_house_index[i] += (*is_reversed ? -1 : 1);
	//std::cerr << _house_index[i] << std::endl;
	
	return true;	
}
void Game::ambush_pacman(Ghost &ghost, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos = ghost.get_map_coordinate();
    if(!is_pacman_moved && cur_pos == arrival_pos)
		return;

	if(_map(cur_pos).is_intersection() && cur_pos == arrival_pos) {
        for(auto const &iter : _map._cst_vertices) {
            if(iter.get_vertex_block().get_map_coordinate() == cur_pos){
                sf::Vector2i target_intersection = arriving_intersection_of(_pacman, false);
                if(cur_pos != target_intersection) {
                    std::vector<struct Vertex::Path> &spaths = _map.shortest_route(iter.get_vertex_block(), _map(target_intersection));
                    ghost.set_path(spaths);
                }
                else {
                    target_intersection = arriving_intersection_of(_pacman, true);
                    if(target_intersection != cur_pos) {
                        std::vector<struct Vertex::Path> &spaths = _map.specified_route(iter.get_vertex_block(), _map(target_intersection));
                        ghost.set_path(spaths);
                    }
                }
            }
        }
    }
	sf::Vector2i displacement = ghost.get_cur_pos();
	ghost.next();
	displacement = ghost.get_cur_pos() - displacement;
	//std::cerr<<displacement.x << " " << displacement.y<< std::endl;
	move_creature(ghost, displacement, arrival_pos);
}
void Game::chase_pacman(Ghost &ghost, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos = ghost.get_map_coordinate();
    if(!is_pacman_moved && cur_pos == arrival_pos)
		return;


	if(_map(cur_pos).is_intersection()) {
		for(auto const &iter : _map._cst_vertices) {
			if(iter.get_vertex_block().get_map_coordinate() == cur_pos && cur_pos == arrival_pos){
				sf::Vector2i target_intersection = arriving_intersection_of(_pacman, true);
				if(cur_pos != target_intersection) {
					std::vector<struct Vertex::Path> &spaths = _map.shortest_route(iter.get_vertex_block(), _map(target_intersection));
					ghost.set_path(spaths);
				}
				else {
					target_intersection = arriving_intersection_of(_pacman, false);
					if(target_intersection != cur_pos) {
						std::vector<struct Vertex::Path> &spaths = _map.specified_route(iter.get_vertex_block(), _map(target_intersection));
						ghost.set_path(spaths);
					}
				}			
				break;
			}
		}
	}
	sf::Vector2i displacement = ghost.get_cur_pos();
	ghost.next();
	displacement = ghost.get_cur_pos() - displacement;
	move_creature(ghost, displacement, arrival_pos);
}
sf::Vector2i Game::arriving_intersection_of(const Creature &creature,bool closest) {
	sf::Vector2i creature_pos = creature.get_map_coordinate();
	sf::Vector2i v1, v2, closest_v, second_closest_v;

	for(const auto& edge_iter : _map._cst_edges) {
		v1 = edge_iter.get_vertices().front()->get_map_coordinate();
		v2 = edge_iter.get_vertices().back()->get_map_coordinate();
		if(v1 == creature_pos)
			return creature_pos;
		if(v2 == creature_pos)
			return creature_pos;

		for(const auto& block_iter : edge_iter.get_route()) {
			if(block_iter->get_map_coordinate() == creature_pos) {
				v1 -= creature_pos;
				v2 -= creature_pos;
				
				if(std::hypot(v1.x, v1.y) <= std::hypot(v2.x, v2.y)) {
					closest_v = v1 + creature_pos;
					second_closest_v = v2 + creature_pos;
				}
				else {
					closest_v = v2 + creature_pos;
					second_closest_v = v1 + creature_pos;
				}

				if (closest)
					return closest_v;
				else
					return second_closest_v;
			}
		}
	}
	return sf::Vector2i(0,0);
}