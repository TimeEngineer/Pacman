#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "woption.hh"
#include "autoposimage.hh"
#include "sound.hh"
#include "resources.hh"


class Background : public AutoPosImage, Sound{
	public:
		Background(unsigned int width, unsigned int height, float scale);
		~Background();
		background_option get_token() const;
		void set_sprite(background_option option);
		static const unsigned int bg_width = 420;
		static const unsigned int bg_height = 460;
	private:
		background_option token;
};