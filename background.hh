#pragma once
#include <SFML/Graphics.hpp>

enum background_option { bMENU = 0, bJEU, bSCORES, bOPTIONS, bCREDITS };

class Background {
	public:
		Background(unsigned int width, unsigned int high);
		~Background();
		sf::Sprite get_sprite() const;
		background_option get_token() const;
		void set_sprite(background_option option);
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		background_option token;
};