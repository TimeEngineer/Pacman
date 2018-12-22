#include "background.hh"


#define SCALE_DEFAULT 1.f
#define SCALE_MEDIUM 2.f

Background::Background(unsigned int width, unsigned int height, Woption option) {
    int sprite_x, sprite_y, offset_x, offset_y;
	float scale;
    // texture size : 420x460
    load_image(_default_path + _image_paths[bMENU]);
	load_sound(_default_path + _sound_path);

	scale = (option != MEDIUM ? SCALE_DEFAULT : SCALE_MEDIUM);
    sprite_x = (width - (get_width() * (int)scale)) >> 1;
    sprite_y = (height - (get_height() * (int)scale)) >> 1;

	set_size(sprite_x, sprite_y, scale, scale);
    token = bMENU;
}

Background::~Background() {}

background_option Background::get_token() const {
	return token;
}

void Background::set_sprite(background_option option) {
	std::string image_path;
	play();
	load_image(_default_path + _image_paths[option]);
	token = option;
}