#pragma once
#include <SFML/Graphics.hpp>
#include "image.hh"
#include "resources.hh"


class Block : public Image{
public:
	Block(const unsigned char block_id);
	Block(const std::string& block_id);
	~Block(){};
	static const std::size_t block_width = 48;
	static const std::size_t block_height = 48;
	unsigned char get_block_id() const {return _block_id;}
private:
	unsigned char _block_id;
};