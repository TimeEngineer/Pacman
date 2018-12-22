#include "map.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>

#define STR_NPOS std::string::npos
Map::Map(std::string map_file)
{
	std::ifstream file(map_file);
	std::string raw_map_data;
	std::size_t pos_begin = 0, pos_end = 0, size, row = 0, col = 0;
	unsigned char **map_data; // size of row * col, filled with integer.
	bool end_loop = false;
	while(file >> raw_map_data) {
		++row;
		do {
			++col;
			pos_begin = raw_map_data.find_first_not_of(',', pos_end);
			pos_end = raw_map_data.find_first_not_of(',', pos_begin + 1);
			
			if(pos_begin == STR_NPOS) {
				std::cerr << "invalid map file" << std::endl;
				exit(0);
			}
			
			end_loop = (pos_end == STR_NPOS);
			size = (end_loop ? pos_end : pos_end - pos_begin);
			
			std::stoi(raw_map_data.substr(pos_begin, size));
			pos_end++;
		}while(end_loop);
	}
	file.close();

}
Map::~Map() 
{
	
}