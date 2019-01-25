#include "map.hh"
#include "edge.hh"
#include "reposize.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#define STR_NPOS std::string::npos

Map::Map(std::string map_file, unsigned int wnd_width,  unsigned int wnd_height, float h_scale, float v_scale):
Graph(),
portals(Block::MAX_PORTAL, NULL),
destinations(Block::MAX_PORTAL, NULL)
{
	std::ifstream file(map_file);
	load_map(file, h_scale, v_scale);
	register_ghost_house(file);
	file.close();
	center_pos(wnd_width, wnd_height);
	link_portals();
	generate_graph();

}
Map::~Map() {}

void Map::load_map(std::ifstream &file, float h_scale, float v_scale) {
	std::string map_str, block_id;
	std::size_t pos_begin = 0, pos_end = 0;
	bool eom_flag = false;
	while(file >> map_str) {
		map_data.push_back(std::vector<Block>());
		_map_dimension.x = pos_begin = pos_end = 0; //Init

		while(pos_end < map_str.length()) {
			std::vector<Block> &row_data = map_data.back(); //A row of the map.

			block_id = parse_next_block(map_str, pos_begin, pos_end);
			if(!block_id.compare(END_OF_ROW)) break;
			eom_flag = !block_id.compare(END_OF_MAP);
			if(eom_flag) break;

			row_data.push_back(Block(block_id, _map_dimension.x, _map_dimension.y));
			row_data.back().set_scale(h_scale, v_scale);
			_map_dimension.x++;
		}
		_map_dimension.y++;
		if(eom_flag) break;
	}
}

void Map::register_ghost_house(std::ifstream &file) {
	std::string map_str, block_id;
	std::size_t pos_begin = 0, pos_end = 0;
	sf::Vector2i house_coordinate;
	int line = 0;
	while(file >> map_str) {
		pos_begin = 0, pos_end = 0;
		_house_index[line++] = static_cast<int>(_ghost_house.size());

   	 	while(pos_end < map_str.length() - 1) {
			house_coordinate = parse_next_coordinate(map_str, pos_begin, pos_end);
			if(house_coordinate.x == -1 || house_coordinate.y == -1) {
				_house_index[line] = static_cast<int>(_ghost_house.size());
				return;
			}
			_ghost_house.push_back(house_coordinate);
		}
	}
}
void Map::center_pos(unsigned int wnd_width,  unsigned int wnd_height) {
	int block_id;

	_block_size = calc_rescaled_size(map_data[0][0].get_size(), map_data[0][0].get_scale());
	_topleft = calc_topleft(sf::Vector2i(wnd_width,wnd_height), _map_dimension,  _block_size);

	for (int row = 0; row < _map_dimension.y; row++) {
		for (int col = 0; col < _map_dimension.x; col++) {
			block_id = map_data[row][col].get_block_id();
			map_data[row][col].set_offset(_topleft.x, _topleft.y);
			map_data[row][col].set_screen_coordinate(col * _block_size.x, row * _block_size.y);

			if (Block::is_portal(map_data[row][col]))
				portals[block_id / 2 - 1] = &map_data[row][col];
			else if (Block::is_gateway(map_data[row][col]))
				destinations[block_id / 2] = &map_data[row][col];
			else if (Block::is_intersection(map_data[row][col]))
				intersections.push_back(&map_data[row][col]);
		}
	}
}
void Map::link_portals() {
	for (int index = 0; index < Block::MAX_PORTAL; index++) {
		if(portals[index] != NULL && destinations[index] != NULL) {
			portals[index]->set_destination(*destinations[index]);
		}
	}
}
void Map::link_adjacent_tiles(int x, int y) {
	if(Block::is_wall(map_data[y][x]) || map_data[y][x].is_linked())
		return;

	Block *alternative_path, *east_block, *west_block, *south_block, *north_block;

	alternative_path = (Block::is_portal(map_data[y][x]) ? &get_real_block_at(x,y) : NULL);

	east_block = (x + 1 >= _map_dimension.x ? alternative_path : &get_real_block_at(x + 1, y));
	west_block = (x - 1 < 0 ? alternative_path : &get_real_block_at(x - 1, y));
	south_block = (y + 1 >= _map_dimension.y ? alternative_path : &get_real_block_at(x, y + 1));
	north_block = (y - 1 < 0 ? alternative_path : &get_real_block_at(x, y - 1));

	map_data[y][x].set_adjacent_tiles(east_block, west_block, south_block, north_block);
}
void Map::generate_graph() {
	for (int y = 0; y < _map_dimension.y; y++) {
		for (int x = 0; x < _map_dimension.x; x++) {
			link_adjacent_tiles(x, y);
		}
	}
	this->generate(intersections);
	this->associate_map_and_graph();
/*
	for (const auto& iter : this->_cst_edges) {
		std::cout << iter << std::endl;
	}
	*/
	/*std::cout << "Now:" << std::endl;
	for (const auto& viter : this->_cst_vertices) {
		for (const auto& eiter : viter.get_paths())
			std::cout << *(eiter.edge) << std::endl;
	}*/
	//std::cout << "Shortest route?" << std::endl;
	//sf::Clock clock;
	//clock.restart();
	//std::vector<struct Vertex::Path> paths = shortest_route(*intersections.back(), *intersections.front());
	/*std::cout << clock.getElapsedTime().asMilliseconds() << "ms" << std::endl;
	int weight = 0;
	for(auto &iter : paths) {
		std::cout<< *iter.edge <<std::endl;
		weight += iter.edge->get_weight();
	}
		std::cout<< "Weight:" << weight <<std::endl;*/
//	
//	std::cout << << std::endl;
	
}

std::string Map::parse_next_block(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end) {
	std::size_t len = 0;
	pos_begin = map_str.find_first_not_of(',', pos_end);
	pos_end = map_str.find_first_of(',', pos_begin + 1);
	
	if(pos_begin == STR_NPOS)
		return END_OF_ROW;
	len =  (pos_end == STR_NPOS ? pos_end : pos_end - pos_begin);
	return map_str.substr(pos_begin, len);
}
sf::Vector2i Map::parse_next_coordinate(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end)
{
	std::size_t pos_middle;
	int x, y;
	pos_begin = map_str.find_first_not_of(';', pos_end);
	pos_middle = map_str.find_first_of(',', pos_begin + 1);
	pos_end = map_str.find_first_of(';', pos_middle + 1);
	
	if(pos_begin == STR_NPOS) sf::Vector2i(-1,-1);
	x = std::stoi(map_str.substr(pos_begin, pos_middle - pos_begin));
	y = std::stoi(map_str.substr(pos_middle + 1, (pos_end - 1) - pos_middle));
	//std::cerr<< map_str.substr(pos_begin, pos_middle - pos_begin) << "," << map_str.substr(pos_middle + 1, (pos_end - 1) - pos_middle) << std::endl;		
	//std::cerr<< x << " " << y << std::endl;		
	
	return sf::Vector2i(x, y);
}
void Map::draw(sf::RenderWindow& window) const {
	for(const auto& iter_row : map_data)
		for(const auto& iter_col : iter_row)
			iter_col.draw(window);
}
