#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
		sf::SoundBuffer buffer;
		sf::Sound sound;
		background_option token;
};