#pragma once
#include <SFML/Graphics.hpp>
#include "map.hh"
#include "pacman.hh"
#include "resources.hh"
#include "entity.hh"
class Game 
{
public:
    Game(unsigned int wnd_width, unsigned int wnd_height, float scale);
    ~Game() {}
    bool move_pacman(sf::Keyboard::Key dir);
    bool check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement);
    void draw(sf::RenderWindow &window);
	bool timer(sf::Clock &clock);
	bool animate_pacman(sf::Clock &clock);
private:
    Map _map;
    Pacman _pacman;
    sf::Vector2i _pacman_pos;
    const int _initial_map_x = 11;
    const int _initial_map_y = 16;
};