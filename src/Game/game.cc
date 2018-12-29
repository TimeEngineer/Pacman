#include "./Game/game.hh"
#include <iostream>
#define FLOAT_CAST(i) static_cast<float>(i)

Game::Game(unsigned int wnd_width, unsigned int wnd_height, float scale):
_map(_default_path + _map_file, wnd_width, wnd_height, scale, scale),
_pacman(scale),
_blinky(scale),
_clyde(scale),
_inkey(scale),
_pinky(scale)
{
    sf::Vector2i offset = _map.get_topleft();
    _pacman.set_offset(offset);
    _inkey.set_offset(offset);
    _blinky.set_offset(offset);
    _clyde.set_offset(offset);
    _pinky.set_offset(offset);


    move_creature(_pacman, _initial_map_x, _initial_map_y);
    move_creature(_blinky, _blinky_init_x, _blinky_init_y);
    move_creature(_clyde, _clyde_init_x, _clyde_init_y);
    move_creature(_inkey, _inkey_init_x, _inkey_init_y);
    move_creature(_pinky, _pinky_init_x, _pinky_init_y);
}

bool Game::move_pacman(sf::Keyboard::Key dir)
{
    bool bMovable = false;
    sf::Vector2i displacement, cur_pos(_pacman.get_map_coordinate()),target_pos;
    switch(dir) {
        case sf::Keyboard::Up :
            displacement.y = -1;
            _pacman.set_orientation(Creature::Orientation::Top);
        break;
        case sf::Keyboard::Down :
            displacement.y = 1;
            _pacman.set_orientation(Creature::Orientation::Bottom);
        break;
        case sf::Keyboard::Left :
            displacement.x = -1;
            _pacman.set_orientation(Creature::Orientation::Left);
        break;
        case sf::Keyboard::Right :
            displacement.x = 1;
            _pacman.set_orientation(Creature::Orientation::Right);
        break;
        default:
        break;
    }
    if(check_mobility(_pacman, cur_pos, displacement))
        return false;
    target_pos = cur_pos + displacement;
    move_creature(_pacman, target_pos);
    return bMovable;
}
void Game::draw(sf::RenderWindow &window)
{
    _map.draw(window);
    _pacman.draw(window);
    _blinky.draw(window);
    _clyde.draw(window);
    _inkey.draw(window);
    _pinky.draw(window);
}


bool Game::check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement)
{
    sf::Vector2i target_pos(cur_pos + displacement);
    
    //target_pos = _map.get_map_coordinate(target_pos);
    
    if(target_pos.x < 0 || target_pos.y < 0)
        return false;
    if(target_pos.x >= _map.get_map_dimension().x || target_pos.y >= _map.get_map_dimension().y)
        return false;
        
    if((_map(target_pos.x, target_pos.y).get_status() & creature.get_entity_id()) != 0x0)
        return false;
    return true;
}
bool Game::timer(sf::Clock &clock)
{
    return true;
}
void Game::animate_pacman(void)
{
    _pacman.next_frame();
}
void Game::move_creature(Creature &creature, const sf::Vector2i &pos)
{
    creature.set_map_coordinate(_map.get_map_coordinate(pos.x, pos.y));
    creature.set_screen_coordinate(_map.get_screen_coordinate(creature.get_map_coordinate()));

}
void Game::move_creature(Creature &creature, int x, int y)
{
   move_creature(creature, sf::Vector2i(x, y));
}
/*
sf::Vector2i Game::map_to_screen_coordinate(sf::Vector2i map_coordinate)
{
    return  _map.get_screen_coordinate(map_coordinate);
}
sf::Vector2i Game::map_to_screen_coordinate(int x, int y)
{
    return _map.get_screen_coordinate(x,y);
}*/
/*sf::Vector2i Game::screen_to_map_coordinate(sf::Vector2i screen_coordinate){return map_to_screen_coordinate(screen_coordinate.x, screen_coordinate.y);}
sf::Vector2i Game::screen_to_map_coordinate(int x, int y){}*/