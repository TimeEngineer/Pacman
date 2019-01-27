#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include "pacman.hh"
#include "ghost.hh"
#include "point.hh"
#include "energizer.hh"
#include "map.hh"
#include "resources.hh"


class Game {
    typedef sf::Vector2i (*router_fnc)(bool closest);
    public:
        //////////////////////////////////////////////////
        // Constructor / Destructor
        Game( unsigned int wnd_width, unsigned int wnd_height, float scale);
        ~Game();

        //////////////////////////////////////////////////
        // Initialization 
        void start() {
            _game_start = true; 
            if(!_game_over) {
                _bg_sound->loop();
                _bg_sound->play();
            }
        }
        void stop() {_game_start = false; _bg_sound->stop();}
        void pause() {_game_pause = true;}
        void unpause() {_game_pause = false;}
        void name_is_entered();
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
        bool is_entering_name() {return _enter_name;}
        void append_char_to_name(char ch);
        void backspace_to_name();
    private:
        //////////////////////////////////////////////////
        // Functions related to the game managing
        void level_up();
        //////////////////////////////////////////////////
        // Functions related to the movement
        sf::Vector2i orientation_to_displacement(Creature::Orientation orientation);
        Creature::Orientation displacement_to_orientation(sf::Vector2i displacement);
        bool pacman_transition_phase(sf::Vector2i arrival_pos);
        
        //////////////////////////////////////////////////
        // Draw
        void draw_center_text(sf::RenderWindow &window, std::string line1, std::string line2, int font_size, sf::Color text_color, sf::Color outline_color, float thickness);
        bool _game_start;
        bool _game_pause;
        bool _game_over;
        bool _enter_name;
        std::string _name;
        const unsigned int _wnd_width;
        const unsigned int _wnd_height;

        bool alive;

        Creature::Orientation _pacman_orientation;
        bool _is_pacman_moved;
        

        sf::Vector2i _pacman_arrival_pos;

        Map _map;
        Pacman _pacman;
        Blinky _blinky;
        Clyde _clyde;
        Inkey _inkey;
        Pinky _pinky;
        std::vector<Point> _points;
        std::vector<Energizer> _energizers;       
        
        int _house_index[6];
        bool _play_sound;
		
        Sound *_chomp_sound;
        Sound *_death_sound;
        Sound *_extra_life_sound;
        Sound *_bg_sound;
        Sound *_alert_sound;
 
        int _target_score;
        int _score_count;   
        int _level;    

        float _scale;
        sf::Vector2i _offset;
        sf::Font _font;
        bool _alert;

};
