#pragma once
#include <SFML/Graphics.hpp>
#include "image.hh"
#include "woption.hh"
class AutoPosImage : public Image {
public:
    AutoPosImage(std::string image_path, unsigned int sc_width, unsigned int sc_height, unsigned int bg_width, unsigned int bg_hight, int offset_x, int offset_y, float scale);
    ~AutoPosImage() {};
};