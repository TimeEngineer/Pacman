#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "autoposimage.hh"
#include "sound.hh"
#include "resources.hh"


class Background {
	public:
		Background(unsigned int width, unsigned int height, float scale);
		~Background();
		background_option get_token() const;
		void set_sprite(background_option option);
		sf::Vector2i get_offset() {return _image.get_offset();}
		static const int bg_width = 420;
		static const int bg_height = 460;
    	void draw(sf::RenderWindow& window) {window.draw(_image.get_sprite());}
	private:
		AutoPosImage _image;
		background_option _token;
		Sound _sound;
};