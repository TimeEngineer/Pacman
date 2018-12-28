#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./Graphics/autoposimage.hh"
#include "./Audio/sound.hh"
#include "./Game/background.hh"
#include "resources.hh"


class Cursor {
	public:
		enum class Direction {Up = 0, Down = 1};
		Cursor(unsigned int width, unsigned int height, float scale, int selection, int limit_min, int limit_max);
		~Cursor();
		void move(Direction dir);
		int get_selection() const {return _selection;}
		int get_limit_min() const {return _limit_min;}
		int get_limit_max() const {return _limit_max;}
		bool get_visible() const {return _image.get_visible();}
		void set_visible(bool visible);
		void set_limit_min(int limit_min);
		void set_limit_max(int limit_max);
   		void draw(sf::RenderWindow& window) {window.draw(_image.get_sprite());}
	private:
		const int default_offset_x = 170;
		const int default_offset_y = 210;
		const int vertical_spacing = 34.5f;
		AutoPosImage _image;
		Sound _sound;
		int _selection;
		int _limit_min;
		int _limit_max;
};