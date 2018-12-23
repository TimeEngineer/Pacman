#include "background.hh"

Background::Background(unsigned int width, unsigned int height, float _scale):
AutoPosImage(_default_path + _bg_image_paths[bMENU], // image_path
			 width, height, // Size of screen.
			 bg_width, bg_height, // Size of background sprite.
			 0, 0, // offset of image pos.
			 _scale) // scale.
{
	load_sound(_default_path + _sound_paths[sCHOICE]);
	token = bMENU;
}

Background::~Background() {}

background_option Background::get_token() const {
	return token;
}

void Background::set_sprite(background_option option) {
	std::string image_path;
	load_image(_default_path + _bg_image_paths[option]);
	token = option;
	if(token == bMENU) {
		loop();
		play();
	}
	else {
		stop();
	}
}