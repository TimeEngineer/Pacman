#include "./Map/map.hh"
#include "./Map/edge.hh"
#include "./Window/reposize.hh"
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
			
			row_data.push_back(new Block(block_id, _map_dimension.x, _map_dimension.y));
			row_data.back()->set_scale(h_scale, v_scale);
			_map_dimension.x++;
		}
		_map_dimension.y++;
	}
	file.close();
	center_pos(wnd_width, wnd_height);
	link_portals();
	for (int y = 0; y < _map_dimension.y; y++) {
		for (int x = 0; x < _map_dimension.x; x++) {
	
			link_adjacent_tiles(x, y);
		}
	}
	for (const auto& iter : intersections) {
		while(!iter->is_visited()) {
			Edge edge(iter);
			std::cout<< "-----------" << std::endl;
		}
		std::cout<< "***************" << std::endl;
	}
}
void Map::center_pos(unsigned int wnd_width,  unsigned int wnd_height)
{
	int block_id;

	_block_size = calc_rescaled_size(map_data[0][0]->get_size(), map_data[0][0]->get_scale());
	_topleft = calc_topleft(sf::Vector2i(wnd_width,wnd_height), _map_dimension,  _block_size);
	
	for (int row = 0; row < _map_dimension.y; row++) {
		for (int col = 0; col < _map_dimension.x; col++) {
			block_id = map_data[row][col]->get_block_id();
			map_data[row][col]->set_offset(_topleft.x, _topleft.y);
			map_data[row][col]->set_screen_coordinate(col * _block_size.x, row * _block_size.y);

			if (Block::is_portal(*map_data[row][col])) 
				portals[block_id / 2 - 1] = map_data[row][col];
			else if (Block::is_gateway(*map_data[row][col]))
				destinations[block_id / 2] = map_data[row][col];
			else if (Block::is_intersection(*map_data[row][col]))
				intersections.push_back(map_data[row][col]);
		}
	}
}
void Map::link_portals()
{
	for (int index = 0; index < Block::MAX_PORTAL; index++) {
		if(portals[index] != NULL && destinations[index] != NULL) {
			portals[index]->set_destination(*destinations[index]);
		}
	}
}
void Map::link_adjacent_tiles(int x, int y)
{
	if(Block::is_wall(*map_data[y][x]) || map_data[y][x]->is_linked())
		return;
	Block *east_block, *west_block, *south_block, *north_block, *alternative_path;
	if(Block::is_portal(*map_data[y][x]))  {
		alternative_path = map_data[y][x];
		std::cout<<"Portal(" << x << " " << y <<") Links to Gateway (" << alternative_path->get_map_coordinate_x() << " "<< alternative_path->get_map_coordinate_y() << ")" << std::endl;
	}
	else
		alternative_path = NULL;
	std::cout<< x  << " " << y << "Linked" << std::endl;
	east_block = (x + 1 >= _map_dimension.x ? alternative_path : map_data[y][x + 1]);
	west_block = (x - 1 < 0 ? alternative_path : map_data[y][x - 1]);
	south_block = (y + 1 >= _map_dimension.y ? alternative_path : map_data[y + 1][x]);
	north_block = (y - 1 < 0 ? alternative_path : map_data[y - 1][x]);
	if(east_block != NULL)
	east_block = map_data[east_block->get_map_coordinate_y()][east_block->get_map_coordinate_x()];
	if(west_block != NULL)
	west_block = map_data[west_block->get_map_coordinate_y()][west_block->get_map_coordinate_x()];
	if(south_block != NULL)
	south_block = map_data[south_block->get_map_coordinate_y()][south_block->get_map_coordinate_x()];
	if(north_block != NULL)
	north_block = map_data[north_block->get_map_coordinate_y()][north_block->get_map_coordinate_x()];
	map_data[y][x]->set_adjacent_tiles(east_block, west_block, south_block, north_block);
	//->linked();
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
