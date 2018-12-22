#pragma once
#include <SFML/Graphics.hpp>


class Block {
public:
	Block(unsigned char block_id);
	~Block();
	static const std::size_t width = 48;
	static const std::size_t height = 48;
private:
	sf::Sprite sprite;
	sf::Texture texture;
	
};