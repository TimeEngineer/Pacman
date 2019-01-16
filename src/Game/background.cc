#include "background.hh"

Background::Background(unsigned int width, unsigned int height, float _scale) :
_image(_default_path + _bg_image_paths[background_option::bMENU], // image_path
			 width, height, // Size of screen.
			 bg_width, bg_height, // Size of background sprite.
			 0, 0, // offset of image pos.
			 _scale), // scale.
_token(background_option::bMENU)
{
	
	_sound.load_sound(_default_path + _sound_paths[sound_option::sCHOICE]);
	_sound.play();
	_sound.loop();
	_token = background_option::bMENU;
}

Background::~Background() {}

background_option Background::get_token() const {
	return _token;
}

void Background::set_sprite(background_option option) {
	std::string image_path;
	_image.load_image(_default_path + _bg_image_paths[option]);
	_token = option;
	if(_token == background_option::bMENU) {
		_sound.loop();
		_sound.play();
	}
	else {
		_sound.stop();
	}
}