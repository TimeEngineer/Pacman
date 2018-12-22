#pragma once
#include <SFML/Graphics.hpp>
#include "block.hh"

class Map {
public:
	Map(std::string map_file);
	~Map();
};