#include "game.hh"
#include <iostream>
#define FLOAT_CAST(i) static_cast<float>(i)
Game::Game(unsigned int wnd_width, unsigned int wnd_height, float scale):
_map(_default_path + _map_file, wnd_width, wnd_height, scale),
_pacman(scale)
{
    _pacman.set_map_x(_initial_map_x);
    _pacman.set_map_y(_initial_map_y);
    _pacman_pos = _map.get_coordinate_screen(_initial_map_x, _initial_map_y);
    _pacman.set_offset(_map.get_topleft_x() + _map.get_block_width() / 2, _map.get_topleft_y() + _map.get_block_height() / 2);
    _pacman.set_position(_pacman_pos.x, _pacman_pos.y);
    //std::cout<<_map.get_topleft_x() + _map.get_block_width() / 2 <<" "  << _map.get_topleft_y() + _map.get_block_height() / 2 << std::endl;
    //_pacman.set_origin(_map.get_block_width() / 2, _map.get_block_height() / 2);
    _pacman.enable_origin_at_center();
}

bool Game::move_pacman(sf::Keyboard::Key dir)
{
    bool bMovable = false;
    sf::Vector2i displacement, cur_pos(_pacman.get_map_x(), _pacman.get_map_y()),target_pos;
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
    _pacman_pos = _map.get_coordinate_screen(target_pos.x, target_pos.y);
    _pacman.set_map_x(_map.get_coordinate_map(target_pos.x, target_pos.y).x);
    _pacman.set_map_y(_map.get_coordinate_map(target_pos.x, target_pos.y).y);
    _pacman.set_position(_pacman_pos.x, _pacman_pos.y);
    return bMovable;
}
void Game::draw(sf::RenderWindow &window)
{
    _map.draw(window);
    window.draw(_pacman.get_sprite());
}

bool Game::check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement)
{
    sf::Vector2i target_pos(cur_pos + displacement);
    if(target_pos.x < 0 || target_pos.y < 0)
        return false;
//    std::cout<<(int)(_map.get_block_status(target_pos.x, target_pos.y))<<std::endl;
  //  std::cout<<(int)(creature.get_entity_id())<<std::endl;
    if((_map.get_block_status(target_pos.x, target_pos.y) & creature.get_entity_id()) != 0x0)
        return false;
    return true;
}
bool Game::timer(sf::Clock &clock)
{
    return true;
}
bool Game::animate_pacman(sf::Clock &clock)
{
    const int anim_milliseconds_pacman = 50;
    sf::Time timer = clock.getElapsedTime();
    if(timer.asMilliseconds() > anim_milliseconds_pacman){
        _pacman.next();
        return true;
    }
    return false;
}