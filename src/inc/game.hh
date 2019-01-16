#pragma once
#include <SFML/Graphics.hpp>
#include "pacman.hh"
#include "ghost.hh"
#include "map.hh"
#include "resources.hh"
class Game 
{
public:
    enum class GhostBehavior{Chase, Random, Ambush, Patrol, Scatter,Frightened};
	//typedef void (Game::*time_func) (void); 
    Game( unsigned int wnd_width, unsigned int wnd_height, float scale);
    ~Game() {}
    bool move_ghost(Ghost &ghost, const sf::Vector2i& pos);
    bool move_ghost(Ghost &ghost, int x, int y);
    bool move_pacman(sf::Keyboard::Key dir);
    bool check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement);
    void draw(sf::RenderWindow &window);
	bool timer(sf::Clock &clock);
	void chase_pacman(void);
	void animate_pacman(void);
	void animate_blinky(void);
	void animate_inkey(void);
	void animate_clyde(void);
	void animate_pinky(void);
    void move_creature(Creature &creature, const sf::Vector2i& pos);
    void move_creature(Creature &creature, int x, int y);
    void order_ghost(Ghost_Sprite::GHOST_TYPE ghost_type, Game::GhostBehavior mode);
    bool exit_ghost_house(Ghost_Sprite::GHOST_TYPE ghost_type);
    sf::Vector2i closest_intersection_to_pacman();

    
    //sf::Vector2i map_to_screen_coordinate(sf::Vector2i map_coordinate);
    //sf::Vector2i map_to_screen_coordinate(int x, int y);
    //sf::Vector2i screen_to_map_coordinate(sf::Vector2i screen_coordinate);
    //sf::Vector2i screen_to_map_coordinate(int x, int y);
private:
    bool is_pacman_moved;
    bool is_clyde_out;
    bool is_inkey_out;
    bool is_pinky_out;
    
    Map _map;
    Pacman _pacman;
    Blinky _blinky;
    Clyde _clyde;
    Inkey _inkey;
    Pinky _pinky;
    const int _initial_map_x = 11;
    const int _initial_map_y = 16;
    const int _inkey_init_x = 10;
    const int _inkey_init_y = 10;
    const int _pinky_init_x = 11;
    const int _pinky_init_y = 10;
    const int _blinky_init_x = 11;
    const int _blinky_init_y = 9;
    const int _clyde_init_x = 12;
    const int _clyde_init_y = 10;
};
		typedef void (Game::*TimerFnc)(void);