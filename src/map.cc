#include "map.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#define STR_NPOS std::string::npos

Map::Map(std::string map_file, float scale)
{
	std::ifstream file(map_file);
	std::string map_str;
	std::size_t pos_begin = 0, pos_end = 0, row = 0, col = 0, len = 0;
	
	while(file >> map_str) {
		map_data.push_back(std::vector<Block*>());
		col = pos_begin = pos_end = 0; //Init
		std::cout<<map_str <<std::endl;
		while(pos_begin < map_str.length()) {
			std::vector<Block*> &row_data = map_data.back(); //A row of the map.

			pos_begin = map_str.find_first_not_of(',', pos_end);
			pos_end = map_str.find_first_of(',', pos_begin + 1);
			
			if(pos_begin == STR_NPOS) break;
			len =  (pos_end == STR_NPOS ? pos_end : pos_end - pos_begin);
			row_data.push_back(new Block(map_str.substr(pos_begin,len)));
			row_data.back()->set_size(col * Block::block_width, row * Block::block_height, 1.f, 1.f);
			++col;
		}
		++row;
		//std::cout<<std::endl;
	}
	file.close();
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