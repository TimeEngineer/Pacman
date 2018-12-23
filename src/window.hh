#pragma once
#include <SFML/Graphics.hpp>
#include "background.hh"
#include "menu.hh"
#include "cursor.hh"
#include "woption.hh"
#include "resources.hh"
#include "map.hh"



class Window {
	public:
		Window(unsigned int width, unsigned int height);
		~Window();
		void launch();
	private:

	// Window Event Handlers : 
		void key_pressed(sf::RenderWindow& window, sf::Keyboard::Key key);
		void draw(sf::RenderWindow& window);
		enum DrawMode {Bg = 0, Game = 1};
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
		Woption _option;
		unsigned int _width;
		unsigned int _height;
		float _scale;
		const background_option _options[5] = {bREGLES, bSCORES, bOPTIONS, bCREDITS, bQUIT};
		DrawMode _mode;
};