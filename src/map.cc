#include "map.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#define STR_NPOS std::string::npos
#define BLOCK_WIDTH row_data.back()->get_width()
#define BLOCK_HEIGHT row_data.back()->get_height()

Map::Map(std::string map_file, unsigned int wnd_width,  unsigned int wnd_height, float scale):
_row(0),
_col(0)
{
	std::ifstream file(map_file);
	std::string map_str, block_id;
	std::size_t pos_begin = 0, pos_end = 0;
	
	while(file >> map_str) {
		map_data.push_back(std::vector<Block*>());
		_col = pos_begin = pos_end = 0; //Init
		
		while(pos_begin < map_str.length()) {
			std::vector<Block*> &row_data = map_data.back(); //A row of the map.

			block_id = next_block(map_str, pos_begin, pos_end);
			if(!block_id.compare("---")) break;
			
			row_data.push_back(new Block(block_id));
			//std::cout<< "["<< _col << "," <<  _row  << "]";
			row_data.back()->set_scale(scale);
			++_col;
		}
		++_row;
	}
	file.close();
	center_pos(wnd_width, wnd_height);
}
void Map::center_pos(unsigned int wnd_width,  unsigned int wnd_height)
{
	Block &sample_block = *(map_data.front().front());
	float scale = sample_block.get_scale();
	unsigned int block_width, block_height, x, y, col, row;


	block_width = static_cast<unsigned int>(sample_block.get_width() * scale);
	block_height = static_cast<unsigned int>(sample_block.get_height() * scale);
	
	x = (wnd_width - (_col * block_width)) >> 1;
	y = (wnd_height - (_row * block_height)) >> 1;
	
	row = 0;
	for(const auto& iter_row : map_data) {
		col = 0;
		for(const auto& iter_col : iter_row) {
			iter_col->set_offset(x, y);
			iter_col->set_position(col * block_width, row * block_height);
			++col;
		}
		++row;
	}

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
	destroy();
}
void Map::destroy()
{
	for(const auto& iter_row : map_data)
		for(const auto& iter_col : iter_row)
			delete iter_col;	
}
void Map::draw(sf::RenderWindow& window)
{
	for(const auto& iter_row : map_data)
		for(const auto& iter_col : iter_row)
			window.draw(iter_col->get_sprite());
}