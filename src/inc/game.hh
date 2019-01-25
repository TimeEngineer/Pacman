#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include "pacman.hh"
#include "ghost.hh"
#include "point.hh"
#include "energizer.hh"
#include "map.hh"
#include "resources.hh"

typedef Ghost_Sprite::GHOST_TYPE GHOST_TYPE;
#define WHICH_GHOST(i) (i == GHOST_TYPE::BLINKY ? static_cast<Ghost&>(_blinky) : (i == GHOST_TYPE::CLYDE ? static_cast<Ghost&>(_clyde) : (i == GHOST_TYPE::INKEY ? static_cast<Ghost&>(_inkey) : static_cast<Ghost&>(_pinky))));

class Game {
    typedef sf::Vector2i (*router_fnc)(bool closest);
    public:
        enum class GhostBehavior{Chase, Random, Ambush, Patrol, Scatter,Frightened};
    	//typedef void (Game::*time_func) (void);
        Game( unsigned int wnd_width, unsigned int wnd_height, float scale);
        ~Game();
        bool move_ghost(Ghost &ghost, Creature::Orientation orientation);
        //bool move_ghost(Ghost &ghost, int x, int y);
        void move_pacman(sf::Keyboard::Key dir);
        bool move_creature(Creature &creature, Creature::Orientation orientation, sf::Vector2i &arrival_pos);
        bool move_creature(Creature &creature, sf::Vector2i displacement, sf::Vector2i &arrival_pos);
        bool check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement);
        void draw(sf::RenderWindow &window);
    	bool timer(sf::Clock &clock);

    	void ambush_pacman(Ghost &ghost, sf::Vector2i &arrival_pos);
    	void chase_pacman(Ghost &ghost, sf::Vector2i &arrival_pos);
    	void random_destination(Ghost &ghost, sf::Vector2i &arrival_pos);
    	void patrol(Ghost &ghost, sf::Vector2i &arrival_pos);
    	void scatter(Ghost &ghost, sf::Vector2i &arrival_pos);
        sf::Vector2i arriving_intersection_of(const Creature &creature, bool closest = true);
        
    	void animate_pacman(void);

        void move(Entity &entity, const sf::Vector2i& pos);
        void move(Entity &entity, int x, int y);
        Entity& collision();
        void order_ghost(Ghost_Sprite::GHOST_TYPE ghost_type, Game::GhostBehavior mode);
        bool exit_ghost_house();
        bool back_and_forth(Ghost &ghost);
        void fill_points(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset);
        void fill_energizers(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset);
        void loop();
        bool is_pacman_moving() {return _pacman_transition;}

        
    private:
        void reset();
        sf::Vector2i orientation_to_displacement(Creature::Orientation orientation);
        Creature::Orientation displacement_to_orientation(sf::Vector2i displacement);
        Creature::Orientation _pacman_orientation;
        bool alive;
        bool is_pacman_moved;
        bool is_clyde_out;
        bool is_inkey_out;
        bool is_pinky_out;

        sf::Vector2i _pacman_arrival_pos;
        sf::Vector2i _pinky_arrival_pos;
        sf::Vector2i _inkey_arrival_pos;
        sf::Vector2i _clyde_arrival_pos;
        sf::Vector2i _blinky_arrival_pos;
        sf::Vector2i _random_pos;

        const int moving_step = 1;

        Map _map;
        Pacman _pacman;
        Blinky _blinky;
        Clyde _clyde;
        Inkey _inkey;
        Pinky _pinky;
        std::vector<Point> _points;
        std::vector<Energizer> _energizers;
        const int _initial_map_x = 11;
        const int _initial_map_y = 17;
        const int _inkey_init_x = 10;
        const int _inkey_init_y = 10;
        const int _pinky_init_x = 11;
        const int _pinky_init_y = 10;
        const int _blinky_init_x = 11;
        const int _blinky_init_y = 8;
        const int _clyde_init_x = 12;
        const int _clyde_init_y = 10;
        int _score;
        bool _pacman_transition;
        bool make_transition(Creature &creature, sf::Vector2i arrival_pos);
        bool make_transition_ghost(Creature &creature, sf::Vector2i arrival_pos);
	    int _house_index[6];
        bool _pinky_reversed;
        bool _clyde_reversed;
        bool _inkey_reversed;
        bool _play_sound;
		
		
        Sound *_chomp_sound;
        Sound *_death_sound;
        Sound *_extra_life_sound;

        int score_count;        
};
