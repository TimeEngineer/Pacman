#pragma once
#include <SFML/Graphics.hpp>
#include "./Graphics/image.hh"

class AutoPosImage : public Image {
public:
    AutoPosImage(std::string image_path, int wnd_width, int wnd_height, int bg_width, int bg_height, int offset_x, int offset_y, float scale);
    ~AutoPosImage() {};
};