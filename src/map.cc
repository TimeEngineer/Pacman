#include "map.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#define STR_NPOS std::string::npos
#define BLOCK_WIDTH row_data.back()->get_width()
#define BLOCK_HEIGHT row_data.back()->get_height()

Map::Map(std::string map_file, float scale)
{
	std::ifstream file(map_file);
	std::string map_str, block_id;
	std::size_t pos_begin = 0, pos_end = 0, row = 0, col = 0;
	
	while(file >> map_str) {
		map_data.push_back(std::vector<Block*>());
		col = pos_begin = pos_end = 0; //Init
		
		while(pos_begin < map_str.length()) {
			std::vector<Block*> &row_data = map_data.back(); //A row of the map.

			block_id = next_block(map_str, pos_begin, pos_end);
			if(!block_id.compare("---")) break;
			row_data.push_back(new Block(block_id));
			row_data.back()->set_size(col * BLOCK_WIDTH * scale, row * BLOCK_HEIGHT * scale, scale, scale);

			++col;
		}
		++row;
	}
	file.close();
}
std::string Map::next_block(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end) 
{
	std::size_t len = 0;
	pos_begin = map_str.find_first_not_of(',', pos_end);
	pos_end = map_str.find_first_of(',', pos_begin + 1);
	if(pos_begin == STR_NPOS) 
		return "---";
	len =  (pos_end == STR_NPOS ? pos_end : pos_end - pos_begin);
	return map_str.substr(pos_begin, len);
}
Map::~Map() 
{
	for(const auto& iter_row : map_data) {
		for(const auto& iter_col : iter_row) {
			delete iter_col;	
		}
	}
}
void Map::destroy()
{
	for(const auto& iter_row : map_data) {
		for(const auto& iter_col : iter_row) {
			delete iter_col;	
		}
	}

}
void Map::draw(sf::RenderWindow& window)
{
	for(const auto& iter_row : map_data) {
		for(const auto& iter_col : iter_row) {
			window.draw(iter_col->get_sprite());
		}
	}
}