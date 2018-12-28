#pragma once
#include <SFML/Graphics.hpp>
#include "./Creature/pacman.hh"
#include "./Map/map.hh"
#include "resources.hh"
class Game 
{
public:
	//typedef void (Game::*time_func) (void); 
    Game( unsigned int wnd_width, unsigned int wnd_height, float scale);
    ~Game() {}
    bool move_pacman(sf::Keyboard::Key dir);
    bool check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement);
    void draw(sf::RenderWindow &window);
	bool timer(sf::Clock &clock);
	void animate_pacman(void);
    //sf::Vector2i map_to_screen_coordinate(sf::Vector2i map_coordinate);
    //sf::Vector2i map_to_screen_coordinate(int x, int y);
    //sf::Vector2i screen_to_map_coordinate(sf::Vector2i screen_coordinate);
    //sf::Vector2i screen_to_map_coordinate(int x, int y);
private:
    Map _map;
    Pacman _pacman;
    sf::Vector2i _pacman_pos;
    const int _initial_map_x = 11;
    const int _initial_map_y = 16;
};