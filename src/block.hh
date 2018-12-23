#pragma once
#include <SFML/Graphics.hpp>
#include "image.hh"
#include "resources.hh"


class Block : public Image{
public:
	enum Status{Empty = 0, Filled = 1, Pacman = 2, Ghost0 = 3, Ghost1 = 4, Ghost2 = 5, Ghost3 = 6};
	Block(const unsigned char block_id);
	Block(const std::string& block_id);
	~Block(){};
	static const std::size_t block_width = 24;
	static const std::size_t block_height = 24;
	unsigned char get_block_id() const {return _block_id;}
	unsigned char get_status() const {return _status;}
private:
	unsigned char _block_id;
	unsigned char _status;
};