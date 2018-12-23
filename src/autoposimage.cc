#include "autoposimage.hh"

#define SCALE_DEFAULT 1.f
#define SCALE_MEDIUM 2.f
typedef unsigned int uint;
AutoPosImage::AutoPosImage(std::string image_path, uint sc_width, uint sc_height, uint bg_width, uint bg_hight, int offset_x, int offset_y, float scale) 
: Image(image_path) 
{
    int sprite_x, sprite_y;
    int int_scale = static_cast<int>(scale);
    load_image(image_path);
    set_offset(offset_x * int_scale,  offset_y * int_scale);
    sprite_x = ((sc_width - (bg_width * int_scale)) >> 1);
    sprite_y = ((sc_height - (bg_hight * int_scale)) >> 1);

	set_size(sprite_x, sprite_y, scale, scale);
}