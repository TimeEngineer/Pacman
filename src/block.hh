#pragma once
#include <SFML/Graphics.hpp>
#include "image.hh"
#include "resources.hh"


class Block : public Image{
public:
	enum class Status{Empty = 0xFF,
					 Filled = 0x00,
					 Pacman = 0x01,
					 Ghost0 = 0x02,
					 Ghost1 = 0x04,
					 Ghost2 = 0x08, 
					 Ghost3 = 0x10,
					 Energizer = 0x20,
					 Dot = 0x30};

	Block(const unsigned char block_id);
	Block(const std::string& block_id);
	~Block(){};
	static const std::size_t block_width = 24;
	static const std::size_t block_height = 24;
	unsigned char get_block_id() const {return _block_id;}
	Block::Status get_status() const {return _status;}
private:
	unsigned char _block_id;
	Block::Status _status;
};