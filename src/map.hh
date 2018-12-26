#pragma once
#include <SFML/Graphics.hpp>
#include "block.hh"
#include "pacman.hh"

class Map {
public:
	Map(std::string map_file, unsigned int wnd_width,  unsigned int wnd_height, float scale);
	~Map();
	void draw(sf::RenderWindow& window);
	void destroy();
	Pacman _pacman;
private:
	void center_pos(unsigned int wnd_width,  unsigned int wnd_height);
	std::vector<std::vector<Block*>> map_data;
	std::string next_block(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end);
	unsigned int _row;
	unsigned int _col;
	const std::string END_OF_MAP = "---";
};