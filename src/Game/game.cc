#include "game.hh"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

Game::Game(unsigned int wnd_width, unsigned int wnd_height, float scale):
alive(true),
is_pacman_moved(false),
is_clyde_out(false),
is_inkey_out(false),
is_pinky_out(false),
_map(_default_path + _map_file, wnd_width, wnd_height, scale, scale),
_pacman(scale),
_blinky(scale),
_clyde(scale),
_inkey(scale),
_pinky(scale),
_pacman_transition(false),
_pinky_reversed(false),
_clyde_reversed(false),
_inkey_reversed(false),
_play_sound(false)
{
	_chomp_sound = new Sound(_default_path + _sound_paths[sound_option::sCHOMP]);
	_death_sound = new Sound(_default_path + _sound_paths[sound_option::sDEATH]);
	_extra_life_sound  = new Sound(_default_path + _sound_paths[sound_option::sEXTRAPACMAN]);

	_house_index[Map::House::Blinky] = _map.get_house_index_blinky();
	_house_index[Map::House::Clyde] = _map.get_house_index_clyde();
	_house_index[Map::House::Pinky] = _map.get_house_index_pinky();
	_house_index[Map::House::Inkey] = _map.get_house_index_inkey();
	sf::Vector2i offset = _map.get_topleft();
	_pacman.set_offset(offset);
	_inkey.set_offset(offset);
	_blinky.set_offset(offset);
	_clyde.set_offset(offset);
	_pinky.set_offset(offset);

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	move(_pacman, _initial_map_x, _initial_map_y);
	move(_blinky, _map.ghost_house_at(_house_index[Map::House::Blinky]));
	move(_clyde, _map.ghost_house_at(_house_index[Map::House::Clyde]));
	move(_inkey, _map.ghost_house_at(_house_index[Map::House::Inkey]));
	move(_pinky, _map.ghost_house_at(_house_index[Map::House::Pinky]));
	_blinky.set_speed(1.1f);
	_clyde.set_speed(1.1f);
	_inkey.set_speed(0.9f);
	_pinky.set_speed(0.9f);
	_pacman.set_speed(1.5f);
	_pacman_arrival_pos = _pacman.get_map_coordinate();
	_blinky_arrival_pos = _blinky.get_map_coordinate();
	_clyde_arrival_pos = _clyde.get_map_coordinate();
	_inkey_arrival_pos = _inkey.get_map_coordinate();
	_pinky_arrival_pos =  _pinky.get_map_coordinate();
	
	std::vector<std::pair<int,int> > energy_pos;
	for(int y = 0; y < _map.get_map_row(); y++) {
		for(int x = 0; x < _map.get_map_col(); x++) {
			if(_map(x,y).get_status() == Block::Status::Empty) {
				energy_pos.push_back(std::pair<int,int>(x,y));
			}
		}
	}
	fill_points(energy_pos, scale, offset);
}
Game::~Game()
{
	delete _death_sound;
	delete _chomp_sound;
	delete _extra_life_sound;
}
Creature::Orientation Game::displacement_to_orientation(sf::Vector2i displacement)
{
	Creature::Orientation orientation = Creature::Orientation::Top;
	if (displacement.x == 0 && displacement.y == 1) orientation = Creature::Orientation::Bottom;
	else if (displacement.x == 0 && displacement.y == -1) orientation = Creature::Orientation::Top;
	else if (displacement.x == 1 && displacement.y == 0) orientation = Creature::Orientation::Right;
	else if (displacement.x == -1 && displacement.y == 0) orientation = Creature::Orientation::Left;
	return orientation;

}
sf::Vector2i Game::orientation_to_displacement(Creature::Orientation orientation) {
	sf::Vector2i displacement(0,0);

	switch(orientation) {
		case Creature::Orientation::Top :
			displacement.y = -1;
			break;
		case Creature::Orientation::Bottom :
			displacement.y = 1;
			break;
		case Creature::Orientation::Left :
			displacement.x = -1;
			break;
		case Creature::Orientation::Right :
			displacement.x = 1;
			break;
		default:
			displacement.x = 0;
			displacement.y = 0;
			break;
	}

	return displacement;
}
void Game::move_pacman(sf::Keyboard::Key dir) {
	Creature::Orientation orientation;
	switch(dir) {
		case sf::Keyboard::Left :
		orientation = Creature::Orientation::Left;
		break;
		case sf::Keyboard::Right: 
		orientation = Creature::Orientation::Right;
		break;
		case sf::Keyboard::Down:
		orientation = Creature::Orientation::Bottom;
		break;
		case sf::Keyboard::Up:
		orientation = Creature::Orientation::Top;
		break;
		default:
		break;
	}
	if(move_creature(_pacman, orientation, _pacman_arrival_pos)) {
		is_pacman_moved = true;
		_pacman_orientation = orientation;
	}
	
}
bool Game::move_creature(Creature &creature, Creature::Orientation orientation, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos(creature.get_map_coordinate());
	sf::Vector2i displacement = orientation_to_displacement(orientation);

	if(!check_mobility(creature, cur_pos, displacement))
		return false;
	
	creature.set_orientation(orientation);

	arrival_pos = cur_pos + displacement;
	return true;
}
bool Game::move_creature(Creature &creature, sf::Vector2i displacement, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos(creature.get_map_coordinate());
	Creature::Orientation orientation = displacement_to_orientation(displacement);

	if(!check_mobility(creature, cur_pos, displacement))
		return false;
	
	creature.set_orientation(orientation);
	arrival_pos = cur_pos + displacement;
	return true;
}

bool Game::check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement) {
	sf::Vector2i target_pos(cur_pos + displacement);


	if(target_pos.x < 0 || target_pos.y < 0)
		return false;
	if(target_pos.x >= _map.get_map_dimension().x || target_pos.y >= _map.get_map_dimension().y)
		return false;

	if((_map(target_pos.x, target_pos.y).get_status() & creature.get_entity_id()) == 0x0)
		return false;
	return true;
}


void Game::move(Entity &creature, const sf::Vector2i &pos) {
	// Cela ne change pas la position de l'image.
	creature.set_map_coordinate(_map.get_map_coordinate(pos.x, pos.y));
	// Cela change la position de l'image.
	creature.set_screen_coordinate(_map.get_screen_coordinate(creature.get_map_coordinate()));
}

void Game::move(Entity &creature, int x, int y) {
   move(creature, sf::Vector2i(x, y));
}
void Game::loop() {

	if(alive) {
		_pacman_transition = make_transition(_pacman, _pacman_arrival_pos);
		move_creature(_pacman, _pacman_orientation, _pacman_arrival_pos);
		if(!is_pacman_moved) {
			if(!make_transition(_pinky, _pinky_arrival_pos)) {
				back_and_forth(_pinky);
				move_creature(_pinky, _map.ghost_house_at(_house_index[Map::House::Pinky]) - _pinky.get_map_coordinate(), _pinky_arrival_pos);
			}
			if(!make_transition(_clyde, _clyde_arrival_pos)) {
					back_and_forth(_clyde);
					move_creature(_clyde,_map.ghost_house_at(_house_index[Map::House::Clyde]) -  _clyde.get_map_coordinate(), _clyde_arrival_pos);
			}
			if(!make_transition(_inkey, _inkey_arrival_pos)) {
					back_and_forth(_inkey);
					move_creature(_inkey,_map.ghost_house_at(_house_index[Map::House::Inkey]) -  _inkey.get_map_coordinate(), _inkey_arrival_pos);
			}
		}
		else {
			
			//if(!make_transition(_pinky, _pinky_arrival_pos))
			//	ambush_pacman(_pinky, _pinky_arrival_pos);
			//if(!make_transition(_blinky, _blinky_arrival_pos))
				chase(_pinky, _pinky_arrival_pos, _pacman, true);
				chase(_blinky, _blinky_arrival_pos, _pacman, false);
			//if(!make_transition(_inkey, _inkey_arrival_pos)) 
				patrol(_inkey, _inkey_arrival_pos);
			//if(!make_transition(_clyde, _clyde_arrival_pos)) 
				random_destination(_clyde, _clyde_arrival_pos);
				
		}
	}
}

void Game::draw(sf::RenderWindow &window) {
	sf::Font font;
	font.loadFromFile(_default_path + _font_paths[FONT_TYPE::COMIC]);
	sf::Text text("Score:" + std::to_string(_pacman.get_score()) + " Life" +  std::to_string(_pacman.get_lives()), font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	window.draw(text);
	_map.draw(window);
	for(auto &iter : _points)
		iter.draw(window);
	for(auto &iter : _energizers)
		iter.draw(window);
	if(alive)
		_pacman.draw(window);
	_blinky.draw(window);
	_clyde.draw(window);
	_inkey.draw(window);
	_pinky.draw(window);
	
	//Draw later if pacman is dead.
	if(!alive)
		_pacman.draw(window);
}

void Game::animate_pacman(void) {
	_pacman.next_frame();
	_inkey.next_frame();
	_blinky.next_frame();
	_clyde.next_frame();
	_pinky.next_frame();
}

bool Game::make_transition(Creature &creature, sf::Vector2i arrival_pos) {
	bool is_transiting = true;
	sf::Vector2f screen_displacement, src_screen_pos, dst_screen_pos;
	src_screen_pos = creature.get_screen_float_coordinate();
	dst_screen_pos = _map.get_screen_float_coordinate(arrival_pos);

	if(_map(creature.get_map_coordinate()).is_gateway() && _map(arrival_pos).is_gateway() && (creature.get_entity_id() & Entity::EntityID::Ghost) != 0) {
		collision();
		move(creature, arrival_pos);
		return false;
	}

	if(std::fabs(src_screen_pos.x - dst_screen_pos.x) < 0.9f && std::fabs(src_screen_pos.y - dst_screen_pos.y) < 0.9f) {
		if(_map(arrival_pos).is_portal()){
			move(creature, arrival_pos);
			return false;
		}	
		creature.set_map_coordinate(arrival_pos);
		move(creature, arrival_pos);
		collision();
		is_transiting = false;
	}
	screen_displacement = dst_screen_pos - src_screen_pos;
	screen_displacement.x = creature.get_speed() * (std::fabs(screen_displacement.x) < 0.1 ? 0 : (screen_displacement.x < 0 ? -1 : 1));
	screen_displacement.y = creature.get_speed() * (std::fabs(screen_displacement.y) < 0.1 ? 0 : (screen_displacement.y < 0 ? -1 : 1));
	creature.set_screen_float_coordinate(src_screen_pos + screen_displacement);
	return is_transiting;

}
void Game::fill_points(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset) {
	int nb_points = static_cast<int>(coordinates.size());
	_points = std::vector<Point>(nb_points, Point(scale));
	for (int i = 0; i < nb_points; i++) {
		_points[i].set_offset(offset);
		move(_points[i], coordinates[i].first, coordinates[i].second);
	}
}

void Game::fill_energizers(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset) {
	int nb_energizers = static_cast<int>(coordinates.size());
	_energizers = std::vector<Energizer>(nb_energizers, Energizer(scale));
	for (int i = 0; i < nb_energizers; i++) {
		_energizers[i].set_offset(offset);
		move(_energizers[i], coordinates[i].first, coordinates[i].second);
	}
}

Entity& Game::collision() {
	/*
	if(alive && (_inkey.get_map_coordinate() == _pacman.get_map_coordinate() ||
	_blinky.get_map_coordinate() == _pacman.get_map_coordinate() ||
	_clyde.get_map_coordinate() == _pacman.get_map_coordinate()||
	_pinky.get_map_coordinate() == _pacman.get_map_coordinate())){
		_pacman.die();
		_pacman.set_loop(false);
		_pacman.set_scene(Pacman_Sprite::DEAD);
		_death_sound->play();
		alive = false;
	 	return _inkey;
	}
*/
	for (auto &point : _points)
		if(point.get_map_coordinate() == _pacman.get_map_coordinate() && point.get_visible()) {
			point.set_visible(false);
			_pacman.add_score(10);
			score_count += 10;
			_chomp_sound->play();
			if (_pacman.get_score() >= 2500) {
				score_count = 0;
				_pacman.extra_life();
				_extra_life_sound->play();
			}
			return point;
		}
	return _pacman;
}

void Game::reset() {
	_house_index[Map::House::Blinky] = _map.get_house_index_blinky();
	_house_index[Map::House::Clyde] = _map.get_house_index_clyde();
	_house_index[Map::House::Pinky] = _map.get_house_index_pinky();
	_house_index[Map::House::Inkey] = _map.get_house_index_inkey();
	
	move(_pacman, _initial_map_x, _initial_map_y);
	move(_blinky, _map.ghost_house_at(_house_index[Map::House::Blinky]));
	move(_clyde, _map.ghost_house_at(_house_index[Map::House::Clyde]));
	move(_inkey, _map.ghost_house_at(_house_index[Map::House::Inkey]));
	move(_pinky, _map.ghost_house_at(_house_index[Map::House::Pinky]));
	
	_pacman_arrival_pos = _pacman.get_map_coordinate();
	_blinky_arrival_pos = _blinky.get_map_coordinate();
	_clyde_arrival_pos = _clyde.get_map_coordinate();
	_inkey_arrival_pos = _inkey.get_map_coordinate();
	_pinky_arrival_pos =  _pinky.get_map_coordinate();
	_pacman.set_loop(true);
	_pacman.set_scene(Pacman_Sprite::LIVE);
}