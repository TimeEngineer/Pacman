#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "game.hh"
#include "cursor.hh"
#include "background.hh"
#include "map.hh"
#include "pacman.hh"
#include "menu.hh"
#include "woption.hh"
#include "resources.hh"
#include <iostream>

typedef std::function<void(void)> CallbackFunction;
class Window {
	public:
		Window(unsigned int width, unsigned int height);
		~Window();
		int get_width() const {return _width;}
		int get_height() const {return _height;}
		void launch();
		void register_timer_event(int time_ms,  CallbackFunction event);
	private:
		//typedef void(Game::*GameFunc)(void);
		struct timer_event {
			CallbackFunction event;
			int time_ms;
			sf::Time timer;
		};
		std::vector<struct timer_event*> timer_events; //timer events
		// Window Event Handlers : 
		void key_pressed(sf::RenderWindow& window, sf::Keyboard::Key key);
		void draw(sf::RenderWindow& window);
		void timer(sf::Clock &clock);
		enum class DrawMode {Bg = 0, Game = 1};
		// Key Pressed Handlers:
		void switch_escape(sf::RenderWindow& window);
		void switch_return(sf::RenderWindow& window);
		void switch_arrowkey(sf::RenderWindow& window, sf::Keyboard::Key dir);
		void menu_selected(sf::RenderWindow& window);
		// New screen 
		void show_rules();
		void show_menu();
		void show_scores();
		void move_cursor(sf::Keyboard::Key dir);
		
		void close_window(sf::RenderWindow& window);
		Background *_background;
		Cursor *_cursor;
		Map *_map;
		
		int _width;
		int _height;
		float _scale;
		const background_option _options[5] = {bREGLES, bSCORES, bOPTIONS, bCREDITS, bQUIT};
		DrawMode _mode;
		Game *_game;
};