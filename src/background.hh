#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "woption.hh"
#include "image.hh"
#include "sound.hh"

enum background_option { bMENU = 0, bREGLES = 1, bJEU = 2, bSCORES = 3, bOPTIONS = 4, bCREDITS = 5 };

class Background : public Image, Sound{
	public:
		Background(unsigned int width, unsigned int height, Woption option);
		~Background();
		background_option get_token() const;
		void set_sprite(background_option option);
	private:
		background_option token;
		const std::string _default_path = "./DataBase";
		const std::string _image_paths[5] = {"/Images/Fonds/menu.png", 
											"/Images/Fonds/rules.png", 
											"/Images/Fonds/basic_level.png", 
											"/Images/Fonds/scores.png"};
		const std::string _sound_path = "/Sounds/choice.wav"
};