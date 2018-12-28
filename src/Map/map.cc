#include "./Map/map.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#define STR_NPOS std::string::npos

Map::Map(std::string map_file, unsigned int wnd_width,  unsigned int wnd_height, float h_scale, float v_scale):
portals(Block::MAX_PORTAL, NULL),
destinations(Block::MAX_PORTAL, NULL)
{
	std::ifstream file(map_file);
	std::string map_str, block_id;
	std::size_t pos_begin = 0, pos_end = 0;
	
	while(file >> map_str) {
		map_data.push_back(std::vector<Block*>());
		_map_dimension.x = pos_begin = pos_end = 0; //Init
		
		while(pos_begin < map_str.length()) {
			std::vector<Block*> &row_data = map_data.back(); //A row of the map.

			block_id = next_block(map_str, pos_begin, pos_end);
			if(!block_id.compare(END_OF_MAP)) break;
			
			row_data.push_back(new Block(block_id));
			row_data.back()->set_scale(h_scale, v_scale);
			_map_dimension.x++;
		}
		_map_dimension.y++;
	}
	file.close();
	center_pos(wnd_width, wnd_height);
	link_portals();
}
void Map::center_pos(unsigned int wnd_width,  unsigned int wnd_height)
{
	int block_id;
	Block &sample_block = *(map_data.front().front());
	sf::Vector2f scale = sample_block.get_scale();

	_block_size = sample_block.get_size();
	_block_size = sf::Vector2i(_block_size.x * scale.x, _block_size.y * scale.y);
	
	_topleft.x = static_cast<int>(wnd_width - (_map_dimension.x * _block_size.x)) >> 1;
	_topleft.y = static_cast<int>(wnd_height - (_map_dimension.y * _block_size.y)) >> 1;
	
	for (int row = 0; row < _map_dimension.y; row++) {
		for (int col = 0; col < _map_dimension.x; col++) {
			block_id = map_data[row][col]->get_block_id();
			map_data[row][col]->set_offset(_topleft.x, _topleft.y);
			map_data[row][col]->set_screen_coordinate(col * _block_size.x, row * _block_size.y);
			map_data[row][col]->set_map_coordinate(col,row);

			if(map_data[row][col]->is_portal()) 
				portals[block_id / 2 - 1] = map_data[row][col];
			else if(map_data[row][col]->is_portal_gateway()) 
				destinations[block_id / 2] = map_data[row][col];
		}
	}
}
void Map::link_portals()
{
	for (int index = 0; index < Block::MAX_PORTAL; index++) {
		if(portals[index] != NULL && destinations[index] != NULL) 
			portals[index]->set_destination(*destinations[index]);
	}
}
	
std::string Map::next_block(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end) 
{
	std::size_t len = 0;
	pos_begin = map_str.find_first_not_of(',', pos_end);
	pos_end = map_str.find_first_of(',', pos_begin + 1);
	if(pos_begin == STR_NPOS) 
		return END_OF_MAP;
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
			iter_col->draw(window);
}
Block::Status Map::get_block_status(int x, int y)
{
	return map_data[y][x]->get_status();
}


	/*
	bool linked1[Block::MAX_PORTAL], linked2[Block::MAX_PORTAL];
	int nb_portals;
	sf::Vector2i portal[Block::MAX_PORTAL][2];
	unsigned char block_id;
	for(const auto& iter_row : map_data) {
		for(const auto& iter_col : iter_row) {
			 block_id = iter_col->get_block_id();
			 if(block_id != Block::EMPTY_BLOCK_ID && block_id <= Block::MAX_PORTAL_NUMBERING) {
				 if( block_id % 2 == 0) { // Portals
				 	portal[(block_id - 1) / 2][0] = sf::Vector2i(iter_col->get_cor_x(), iter_col->get_cor_y());
					linked1[(block_id - 1) / 2] = true;
				 }
				 else{ // Exit
				 	portal[block_id / 2][1] = sf::Vector2i(iter_col->get_cor_x(), iter_col->get_cor_y());
					linked2[block_id / 2] = true;
				 }
			 }
		}
	}
	for(int i = 0; i < Block::MAX_PORTAL; i++) {
		if(linked1[i] && linked2[i]) {
			map_data[portal[i][0].y][portal[i][0].x]->set_cor_x(portal[i][1].x);
			map_data[portal[i][0].y][portal[i][0].x]->set_cor_y(portal[i][1].y);
		}
	}*/