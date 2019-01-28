#include "cursor.hh"
#include <iostream>

Cursor::Cursor(unsigned int width, unsigned int height, float scale, int selection, int limit_min, int limit_max) :
_image(_default_path + _image_paths[iCURSOR], // image_path
			 width, height, // Size of screen.
			 Background::bg_width, Background::bg_height, // Size of background sprite.
			 default_offset_x, default_offset_y, // offset of image pos.
			 scale), // scale.			 
_selection(selection),
_limit_min(limit_min),
_limit_max(limit_max)
{
	_sound.load_sound(_default_path + _sound_paths[sound_option::sCURSOR]);
}

Cursor::~Cursor() {}
// Move the cursor up and downward.
void Cursor::move(Direction dir)
{
    _sound.play();
	//Check limit before moving the cursor.
	if(dir == Direction::Down && _selection < _limit_max)
		_selection += 1;
	else if(dir == Direction::Up && _selection > _limit_min)
		_selection += -1;
	else
		return;
	// Move only vertically.
	_image.set_y((vertical_spacing * _image.get_scale().y) * _selection);
}
// Set range of limit for cursor so that it doesn't go out of bound.
void Cursor::set_limit_min(int limit_min)
{
	_limit_min = limit_min;
}
void Cursor::set_limit_max(int limit_max)
{
	_limit_max = limit_max;
}

void Cursor::set_visible(bool visible)
{
	_image.set_visible(visible);
}