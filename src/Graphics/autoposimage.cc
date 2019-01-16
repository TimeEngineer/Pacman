#include "autoposimage.hh"
#include "reposize.hh"
#include <iostream>
#define INT_CAST(i) static_cast<int>(i)
AutoPosImage::AutoPosImage(std::string image_path, int wnd_width, int wnd_height, int bg_width, int bg_height, int offset_x, int offset_y, float scale) 
: Image(image_path) 
{
    sf::Vector2i topleft_pos = calc_topleft( sf::Vector2i(wnd_width, wnd_height), 
                                            sf::Vector2i(bg_width, bg_height), 
                                            sf::Vector2f(scale, scale));
    load_image(image_path);
    set_offset(topleft_pos.x + INT_CAST(offset_x * scale), topleft_pos.y + INT_CAST(offset_y * scale));
	set_scale(scale, scale);
}