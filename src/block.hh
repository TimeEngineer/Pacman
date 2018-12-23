#pragma once
#include <SFML/Graphics.hpp>
#include "image.hh"


class Block : public Image{
public:
	Block(unsigned char block_id);
	~Block(){};
	static const std::size_t block_width = 48;
	static const std::size_t block_height = 48;
private:
	
};