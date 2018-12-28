#include "./Game/game.hh"
#include <iostream>
#define FLOAT_CAST(i) static_cast<float>(i)

Game::Game(unsigned int wnd_width, unsigned int wnd_height, float scale):
_map(_default_path + _map_file, wnd_width, wnd_height, scale, scale),
_pacman(scale)
{
    _pacman.set_offset(_map.get_topleft_x() + _map.get_block_width() / 2, _map.get_topleft_y() + _map.get_block_height() / 2);
    _pacman.set_map_coordinate(_initial_map_x, _initial_map_y);
    _pacman.set_screen_coordinate(_map.get_screen_coordinate(_pacman.get_map_coordinate()));
    _pacman.enable_origin_at_center();
    
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
    _pacman.set_map_coordinate(_map.get_map_coordinate(target_pos));
    _pacman.set_screen_coordinate(_map.get_screen_coordinate(_pacman.get_map_coordinate()));
    return bMovable;
}
void Game::draw(sf::RenderWindow &window)
{
    _map.draw(window);
    _pacman.draw(window);
}


bool Game::check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement)
{
    sf::Vector2i target_pos(cur_pos + displacement);
    
    //target_pos = _map.get_map_coordinate(target_pos);
    
    if(target_pos.x < 0 || target_pos.y < 0)
        return false;
    if(target_pos.x >= _map.get_map_dimension().x || target_pos.y >= _map.get_map_dimension().y)
        return false;
    if((_map.get_block_status(target_pos.x, target_pos.y) & creature.get_entity_id()) != 0x0)
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