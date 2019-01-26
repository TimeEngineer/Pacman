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
        //////////////////////////////////////////////////
        // Constructor / Destructor
        Game( unsigned int wnd_width, unsigned int wnd_height, float scale);
        ~Game();

        //////////////////////////////////////////////////
        // Initialization 
        void start() {_game_start = true;}
        void stop() {_game_start = false;}
        void pause() {_game_pause = true;}
        void unpause() {_game_pause = false;}
        void game_reset();
        bool back_and_forth(Ghost &ghost);
        void fill_points(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset);
        void fill_energizers(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset);
        void reset();

        //////////////////////////////////////////////////
        // Function related to the movement
        bool check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement);
        void move_pacman(sf::Keyboard::Key dir);
        bool move_creature(Creature &creature, Creature::Orientation orientation, sf::Vector2i &arrival_pos);
        bool move_creature(Creature &creature, sf::Vector2i displacement, sf::Vector2i &arrival_pos);
        void move(Entity &entity, const sf::Vector2i& pos);
        void move(Entity &entity, int x, int y);

        //////////////////////////////////////////////////
        // Looping events
        void draw(sf::RenderWindow &window);
    	void animate(void);
        void loop();
        void collision();
    
        //////////////////////////////////////////////////
        // Ghost Behaviors
        void ghost_transition_phase(Ghost &ghost);
    	void chase(Ghost &ghost, Creature &creature, bool ambush = false);
    	void random_destination(Ghost &ghost);
    	void patrol(Ghost &ghost);
    	void scatter(Ghost &ghost);
        sf::Vector2i arriving_intersection_of(const Creature &creature, bool closest = true);
        
        
        //////////////////////////////////////////////////
        // Misc
        bool is_game_started() {return _game_start;}
        bool is_game_paused() {return _game_pause;}
        bool is_game_over() {return _game_over;}
        
        
    private:
        //////////////////////////////////////////////////
        // Function related to the game managing
        void level_up();
        //////////////////////////////////////////////////
        // Function related to the movement
        sf::Vector2i orientation_to_displacement(Creature::Orientation orientation);
        Creature::Orientation displacement_to_orientation(sf::Vector2i displacement);
        bool pacman_transition_phase(sf::Vector2i arrival_pos);
        
        bool _game_start;
        bool _game_pause;
        bool _game_over;
        const unsigned int _wnd_width;
        const unsigned int _wnd_height;

        bool alive;
       
        Creature::Orientation _pacman_orientation;
        bool _is_pacman_moved;
        /*bool _is_clyde_out;
        bool _is_inkey_out;
        bool _is_pinky_out;*/

        sf::Vector2i _pacman_arrival_pos;

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
        
        
        int _house_index[6];
        bool _play_sound;
		
		
        Sound *_chomp_sound;
        Sound *_death_sound;
        Sound *_extra_life_sound;
 
        int _target_score;
        int _score_count;   
        int _level;    

        float _scale;
        sf::Vector2i _offset;
};
