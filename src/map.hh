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
	int get_topleft_x() const {return _topleft_x;}
	int get_topleft_y() const {return _topleft_y;}
	int get_block_width() const {return _block_height;}
	int get_block_height() const {return _block_height;}
	sf::Vector2i get_coordinate_screen(int x, int y) const {return sf::Vector2i(map_data[y][x]->get_cor_x() * _block_width,map_data[y][x]->get_cor_y()* _block_height);}
	sf::Vector2i get_coordinate_map(int x, int y) const {return sf::Vector2i(map_data[y][x]->get_cor_x() ,map_data[y][x]->get_cor_y());}
	Block::Status get_block_status(int x, int y);
private:
	void center_pos(unsigned int wnd_width,  unsigned int wnd_height);
	void link_portals();
	std::vector<std::vector<Block*>> map_data;
	std::string next_block(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end);
	unsigned int _row;
	unsigned int _col;
	const std::string END_OF_MAP = "---";
	int _topleft_x;
	int _topleft_y;
	int _block_width;
	int _block_height;

};