#pragma once
#include <SFML/Graphics.hpp>

class Cursor {
	public:
		Cursor(unsigned int width, unsigned int high);
		~Cursor();
		sf::Sprite get_sprite() const;
		float get_x() const;
		float get_y() const;
		bool get_visible() const;
		void set_sprite(sf::Sprite& s);
		void set_x(float f);
		void set_y(float f);
		void set_visible(bool b);
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		float x;
		float y;
		bool visible;
};