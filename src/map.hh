#pragma once
#include <SFML/Graphics.hpp>
#include "block.hh"

class Map {
public:
	Map(std::string map_file, float scale);
	~Map();
	void draw(sf::RenderWindow& window);
	void destroy();
private:
	std::vector<std::vector<Block*> > map_data;
};