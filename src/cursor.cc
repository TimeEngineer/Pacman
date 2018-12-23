#include "cursor.hh"
#include <iostream>
#define DEFAULT_OFFSET_X 170
#define DEFAULT_OFFSET_Y 210
#define DEFAULT_VSPACING 34.5f
Cursor::Cursor(unsigned int width, unsigned int height, Woption option, int selection, int limit_min, int limit_max) :
AutoPosImage(_default_path + _image_paths[iCURSOR], // image_path
			 width, height, // Size of screen.
			 Background::bg_width, Background::bg_height, // Size of background sprite.
			 DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y, // offset of image pos.
			 (option != MEDIUM ? DEFAULT_SCALE : MEDIUM_SCALE)), // scale.			 
_selection(selection),
_limit_min(limit_min),
_limit_max(limit_max)
{
	_init_x = get_x();
	_init_y = get_y();
	load_sound(_default_path + _sound_paths[sCURSOR]);
}

Cursor::~Cursor() {}

void Cursor::move(Direction dir)
{
    play();
	if(dir == Direction::Down &&_selection < _limit_max)
		_selection += 1;
	else if(dir == Direction::Up &&_selection > _limit_min)
		_selection += -1;
	else
		return;
		
	set_y(_init_y + (DEFAULT_VSPACING * get_scale()) * _selection);
}
void Cursor::set_limit_min(int limit_min)
{
	_limit_min = limit_min;
}
void Cursor::set_limit_max(int limit_max)
{
	_limit_max = limit_max;
}
