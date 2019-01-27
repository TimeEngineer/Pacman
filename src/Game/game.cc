#include "game.hh"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

Game::Game(unsigned int wnd_width, unsigned int wnd_height, float scale):
_game_start(false),
_game_pause(false),
_game_over(false),
_enter_name(false),
_name(""),
_wnd_width(wnd_width),
_wnd_height(wnd_height),
alive(true),
_pacman_orientation(Creature::Orientation::Top),
_is_pacman_moved(false),
/*
_is_clyde_out(false),
_is_inkey_out(false),
_is_pinky_out(false),*/
_pacman_arrival_pos(0,0),
_map(_default_path + _map_file, wnd_width, wnd_height, scale, scale),
_pacman(scale),
_blinky(scale),
_clyde(scale),
_inkey(scale),
_pinky(scale),
_play_sound(false),
_target_score(0),
_level(0),
_scale(scale),
_alert(false)
{
	_font.loadFromFile(_default_path + _font_paths[FONT_TYPE::COMIC]);
	_chomp_sound = new Sound(_default_path + _sound_paths[sound_option::sCHOMP]);
	_death_sound = new Sound(_default_path + _sound_paths[sound_option::sDEATH]);
	_extra_life_sound  = new Sound(_default_path + _sound_paths[sound_option::sEXTRAPACMAN]);
    _bg_sound = new Sound(_default_path + _sound_paths[sound_option::sINTERMISSION]);
    _alert_sound = new Sound(_default_path + _sound_paths[sound_option::sALERT]);
	
	_house_index[Map::House::Blinky] = _map.get_house_index_blinky();
	_house_index[Map::House::Clyde] = _map.get_house_index_clyde();
	_house_index[Map::House::Pinky] = _map.get_house_index_pinky();
	_house_index[Map::House::Inkey] = _map.get_house_index_inkey();
	_offset = _map.get_topleft();
	_pacman.set_offset(_offset);
	_inkey.set_offset(_offset);
	_blinky.set_offset(_offset);
	_clyde.set_offset(_offset);
	_pinky.set_offset(_offset);
	
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	reset();
	game_reset();
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
		case Creature::Orientation::Top : displacement.y = -1; break;
		case Creature::Orientation::Bottom : displacement.y = 1; break;
		case Creature::Orientation::Left : displacement.x = -1; break;
		case Creature::Orientation::Right : displacement.x = 1; break;
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
	
	_is_pacman_moved = true;
	_pacman_orientation = orientation;
}

bool Game::check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement) {
	sf::Vector2i target_pos(cur_pos + displacement);
	if (target_pos.x < 0 || target_pos.y < 0) 
		return false;
	if (target_pos.x >= _map.get_map_dimension().x || target_pos.y >= _map.get_map_dimension().y)
		return false;

	if ((_map(target_pos.x, target_pos.y).get_status() & creature.get_entity_id()) == 0x0)
		return false;
	return true;
}

bool Game::move_creature(Creature &creature, Creature::Orientation orientation, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos(creature.get_map_coordinate());
	sf::Vector2i displacement = orientation_to_displacement(orientation);

	if (!check_mobility(creature, cur_pos, displacement))
		return false;
	
	creature.set_orientation(orientation);
	arrival_pos = cur_pos + displacement;
	
	return true;
}
bool Game::move_creature(Creature &creature, sf::Vector2i displacement, sf::Vector2i &arrival_pos) {
	sf::Vector2i cur_pos(creature.get_map_coordinate());
	Creature::Orientation orientation = displacement_to_orientation(displacement);

	if (!check_mobility(creature, cur_pos, displacement))
		return false;
	
	creature.set_orientation(orientation);
	arrival_pos = cur_pos + displacement;
	return true;
}

bool Game::pacman_transition_phase(sf::Vector2i arrival_pos) {
	bool _is_transiting = true;
	sf::Vector2f screen_displacement, src_screen_pos, dst_screen_pos;
	src_screen_pos = _pacman.get_screen_float_coordinate();
	dst_screen_pos = _map.get_screen_float_coordinate(arrival_pos);

	if (std::fabs(src_screen_pos.x - dst_screen_pos.x) < (_pacman.get_speed() * 1.5f) && std::fabs(src_screen_pos.y - dst_screen_pos.y) < (_pacman.get_speed() * 1.5f)) {
		if (_map(arrival_pos).is_portal()){
			move(_pacman, arrival_pos);
			return false;
		}	
		_pacman.set_map_coordinate(arrival_pos);
		move(_pacman, arrival_pos);
		_is_transiting = false;
	}
	else {
		screen_displacement = dst_screen_pos - src_screen_pos;
		screen_displacement.x = _pacman.get_speed() * (std::fabs(screen_displacement.x) < 0.1 ? 0 : (screen_displacement.x < 0 ? -1 : 1));
		screen_displacement.y = _pacman.get_speed() * (std::fabs(screen_displacement.y) < 0.1 ? 0 : (screen_displacement.y < 0 ? -1 : 1));
		_pacman.set_screen_float_coordinate(src_screen_pos + screen_displacement);
	}
	return _is_transiting;

}

void Game::move(Entity &creature, const sf::Vector2i &pos) {
	// Cela ne change pas la position de l'image.
	creature.set_map_coordinate(_map.get_map_coordinate(pos.x, pos.y));
	// Cela change la position de l'image.
	creature.set_screen_coordinate(_map.get_screen_coordinate(creature.get_map_coordinate()));
}
//Overload of function move
void Game::move(Entity &creature, int x, int y) {
   move(creature, sf::Vector2i(x, y));
}

void Game::loop() {
	if (!_game_start) 
		return;
	if (_game_pause)
		return;
	if (alive) {
		
		collision();

		pacman_transition_phase(_pacman_arrival_pos);
		move_creature(_pacman, _pacman_orientation, _pacman_arrival_pos);
		
		if (!_is_pacman_moved) {
			
		}
		else {
			int close_range = 4;
			sf::Vector2i dist0, dist1, dist2, dist3;
			chase(_pinky, _pacman, true);
			chase(_blinky, _pacman, false);
			patrol(_inkey);
			random_destination(_clyde);
			dist0 = _pacman.get_map_coordinate() - _pinky.get_map_coordinate();
			dist1 = _pacman.get_map_coordinate() - _blinky.get_map_coordinate();
			dist2 = _pacman.get_map_coordinate() - _inkey.get_map_coordinate();
			dist3 = _pacman.get_map_coordinate() - _clyde.get_map_coordinate();
			// Send alert if ghosts are close
			if(std::hypot(dist0.x, dist0.y) <  close_range ||
			std::hypot(dist1.x, dist1.y) < close_range ||
			std::hypot(dist2.x, dist2.y) < close_range ||
			std::hypot(dist3.x, dist3.y) < close_range) {
				if(!_alert) {
					_alert_sound->loop();
					_alert_sound->play();
				}
				_alert = true;
			}
			else if(std::hypot(dist0.x, dist0.y) > close_range &&
			std::hypot(dist1.x, dist1.y) > close_range &&
			std::hypot(dist2.x, dist2.y) > close_range &&
			std::hypot(dist3.x, dist3.y) > close_range) {
				if(_alert) {
					_alert_sound->stop();
				}
				_alert = false;
			}			
		}
	}
}

void Game::draw(sf::RenderWindow &window) {

	sf::Text text("Score : " + std::to_string(_pacman.get_score()) + "   Life : " +  std::to_string(_pacman.get_lives()), _font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	window.draw(text);

	_map.draw(window);
	for (auto &iter : _points)
		iter.draw(window);
	for (auto &iter : _energizers)
		iter.draw(window);
	if (alive)
		_pacman.draw(window);
	_blinky.draw(window);
	_clyde.draw(window);
	_inkey.draw(window);
	_pinky.draw(window);
	
	//Draw later if pacman is dead.
	if (!alive)
		_pacman.draw(window);
	if(_game_over) {
		if(_enter_name) {
			draw_center_text(window, "GAME OVER. Votre nom ? (Entrez)", _name ,30, sf::Color::White, sf::Color::Black, 2.0f);	
		}
		else {
			draw_center_text(window, "GAME OVER", "ECHAPPE POUR RETOURNER AU MENU",30, sf::Color::Black, sf::Color::Red, 2.0f);	
		}
		reset();
		_level = 0;
		return;
	}
	if (!_game_start) {
		draw_center_text(window, "NIVEAU " + std::to_string(_level),"PRET? (TAPEZ ENTREE)",30, sf::Color::Red, sf::Color::White, 2.0f);	
	}
	else {
		if(_game_pause) {
			draw_center_text(window, "PAUSE ", "",30, sf::Color::Red, sf::Color::White, 2.0f);	
		}
	}
}
void Game::draw_center_text(sf::RenderWindow &window, std::string line1, std::string line2, int font_size, sf::Color text_color, sf::Color outline_color, float thickness)
{
	int nb_lines = 0;
	sf::Text text("", _font);	
	text.setCharacterSize(font_size);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(text_color);
	text.setOutlineColor(outline_color);
	text.setOutlineThickness(thickness);
	
	if(line1.size() > 0) nb_lines++;
	if(line2.size() > 0) nb_lines++;
	
	text.setString(line1);
	text.setPosition((_wnd_width - text.getLocalBounds().width) / 2, _wnd_height / 2 - (text.getLocalBounds().height / 2 *nb_lines));
	window.draw(text);
	text.setString(line2);
	text.setPosition((_wnd_width - text.getLocalBounds().width) / 2, _wnd_height /2 + (text.getLocalBounds().height / 2 *(nb_lines - 1)));
	window.draw(text);
}

void Game::animate(void) {
	_pacman.next_frame();
	_inkey.next_frame();
	_blinky.next_frame();
	_clyde.next_frame();
	_pinky.next_frame();
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

void Game::collision() {
	const int nb_ghosts = 4;
	Creature *ghosts[nb_ghosts] = {&_blinky, &_inkey, &_pinky, &_clyde};
	sf::Vector2i dist;
	// Collision between ghosts and pacman
	for (int i = 0; i < nb_ghosts; i++) {
		dist = ghosts[i]->get_screen_coordinate() - _pacman.get_screen_coordinate();
		if(alive && std::hypot(dist.x, dist.y) < (_pacman.get_frame_rect().width / 2) ) {
			_pacman.die();
			_pacman.set_loop(false);
			_pacman.set_scene(Pacman_Sprite::DEAD);
			_alert_sound->stop();
			_bg_sound->stop();
			_death_sound->play();
			_game_start = false;
			alive = false;
			if(_pacman.get_lives() <= 0) {
				_game_over = true;
				_enter_name = true;
				
			}
			return;
		}
	}

	for (auto &point : _points) {
		if (point.get_map_coordinate() == _pacman.get_map_coordinate() && point.get_visible()) {
			// Make dots invisible, add score, play sound.
			point.set_visible(false);
			_pacman.add_score(10);
			_score_count += 10;
			_chomp_sound->play();
			
			// Pacman ate all, then level up : 
			if (_pacman.get_score() > 0 && _pacman.get_score() % _target_score == 0) {
				level_up();
			}
			// Add life for each 500 points.
			if (_pacman.get_score() > 0 && _pacman.get_score() % 500 == 0) {
				_pacman.extra_life();
				_extra_life_sound->play();
			}
		}
	}
}

void Game::level_up() {
	_game_start = false;
	_level++;
	std::vector<std::pair<int,int> > energy_pos;
	_points.clear();
	for (int y = 0; y < _map.get_map_row(); y++) {
		for (int x = 0; x < _map.get_map_col(); x++) {
			if (_map(x,y).get_status() == Block::Status::Empty) {
				energy_pos.push_back(std::pair<int,int>(x,y));
			}
		}
	}
	unsigned int size = energy_pos.size(), factor, i = 0;
	factor = (_level <= 15 ? 17 - _level : 2);
	//Retirer les gommees aleatoirement jusqu'a ce qu'il en reste assez pour le niveau.
	while(energy_pos.size() > size / factor) {
		i = std::rand() % energy_pos.size();
		energy_pos.erase((energy_pos.begin() + i));
	}
	_target_score += static_cast<int>(energy_pos.size()) * 10	;
	fill_points(energy_pos, _scale, _offset);

	for (auto &point : _points) {
		point.set_visible(true);
	}	
}
void Game::game_reset() {
	_name = "";
	_game_start = false;
	_game_over = false;
	_game_pause = false;
	_target_score = 0;
	_level = -1;
	level_up();
	_pacman.set_lives(2);
	_pacman.set_score(0);
	
}
void Game::reset() {
	std::vector<sf::Vector2i> null_path(0, sf::Vector2i(-1,-1));
	_house_index[Map::House::Blinky] = _map.get_house_index_blinky();
	_house_index[Map::House::Clyde] = _map.get_house_index_clyde();
	_house_index[Map::House::Pinky] = _map.get_house_index_pinky();
	_house_index[Map::House::Inkey] = _map.get_house_index_inkey();
	
	move(_pacman, _initial_map_x, _initial_map_y);
	move(_blinky, _map.ghost_house_at(_house_index[Map::House::Blinky]));
	move(_clyde, _map.ghost_house_at(_house_index[Map::House::Clyde]));
	move(_inkey, _map.ghost_house_at(_house_index[Map::House::Inkey]));
	move(_pinky, _map.ghost_house_at(_house_index[Map::House::Pinky]));
	_pacman_orientation = Creature::Orientation::Top;
	_pacman_arrival_pos = _pacman.get_map_coordinate();
	_pacman.set_loop(true);
	_pacman.set_scene(Pacman_Sprite::LIVE);
	_blinky.set_path(null_path);
	_clyde.set_path(null_path);
	_inkey.set_path(null_path);
	_pinky.set_path(null_path);
	_blinky.set_speed(0.7f + (_level * 0.1f));
	_clyde.set_speed(0.7f + (_level * 0.1f));
	_inkey.set_speed(0.6f + (_level * 0.1f));
	_pinky.set_speed(0.6f + (_level * 0.1f));
	_pacman.set_speed(1.5f+ (_level * 0.05f));
	alive = true;
}
void Game::append_char_to_name(char ch) {
	_name += ch;
}
void Game::backspace_to_name() {
	if(_name.size() > 0)
		_name.pop_back();
}

void Game::name_is_entered()
{
	std::ofstream ofs (_leaderboard_filename, std::ofstream::app);
	if(ofs.is_open()) {
		ofs << _name;
		ofs << ";";
		ofs << _pacman.get_score() << std::endl;
	}
	else {
		std::cerr << "Echec d'ouverture : " << _leaderboard_filename << std::endl;
	}
  	ofs.close();
	_enter_name = false;
}