#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "graph.hh"
#include "block.hh"

class Map : public Graph {
public:
	Map(std::string map_file, unsigned int wnd_width,  unsigned int wnd_height, float h_scale, float v_scale);
	~Map();
	void draw(sf::RenderWindow& window) const;
	void destroy();
	//getters
	sf::Vector2i  get_map_dimension() const {return _map_dimension;}
	int get_map_row() const {return _map_dimension.x;}
	int get_map_col() const {return _map_dimension.y;}
	sf::Vector2i  get_topleft() const {return _topleft;}
	int get_topleft_x() const {return _topleft.x;}
	int get_topleft_y() const {return _topleft.y;}
	sf::Vector2i  get_block_size() const {return _block_size;}
	int get_block_width() const {return _block_size.x;}
	int get_block_height() const {return _block_size.y;}
	const Block& operator()(int x, int y) const {return map_data[y][x];}
	const Block& operator()(sf::Vector2i pos) const {return map_data[pos.y][pos.x];}
	// Position of image on the computer screen from the map coordinate
	sf::Vector2i get_screen_coordinate(sf::Vector2i map_coordinate) const {return get_screen_coordinate(map_coordinate.x, map_coordinate.y);}
	sf::Vector2i get_screen_coordinate(int x, int y) const {return map_data[y][x].get_screen_coordinate();}
	sf::Vector2f get_screen_float_coordinate(sf::Vector2i map_coordinate) const {return get_screen_float_coordinate(map_coordinate.x, map_coordinate.y);}
	sf::Vector2f get_screen_float_coordinate(int x, int y) const {return map_data[y][x].get_screen_float_coordinate();}

	// The following methods are needed for portal blocks. 
	// Portal doesn't not have its own coordinates and borrows one from another block.
	// Returns coordinate of the map (Ex) 1th row, 7th column)
	sf::Vector2i get_map_coordinate(sf::Vector2i map_coordinate) const {return get_map_coordinate(map_coordinate.x, map_coordinate.y);}
	sf::Vector2i get_map_coordinate(int x, int y) const {return map_data[y][x].get_map_coordinate();}
	// Returns if the block is empty, filled or portal.
	Block::Status get_block_status(sf::Vector2i map_coordinate) const {return get_block_status(map_coordinate.x, map_coordinate.y);}
	Block::Status get_block_status(int x, int y) const {return map_data[y][x].get_status();}

	
	const std::vector<Block*> &get_intersections() const {return intersections;}

	int get_house_index_blinky() const {return _house_index[House::Blinky];}
	int get_house_index_door() const {return _house_index[House::Door];}
	int get_house_index_pinky() const {return _house_index[House::Pinky];}
	int get_house_index_clyde() const {return _house_index[House::Clyde];}
	int get_house_index_inkey() const {return _house_index[House::Inkey];}
	int get_house_index_end() const {return _house_index[House::End];}
	const sf::Vector2i& ghost_house_at(int index) const {return _ghost_house[index];}
	const sf::Vector2i& get_pacman_init_pos() const {return _pacman_init_pos;}
	enum House {Blinky = 0, Door, Pinky, Inkey, Clyde, End};
private:
	Block& get_apparent_block_at(int x, int y) {return map_data[y][x];}
	Block& get_real_block_at(int x, int y) {return map_data[map_data[y][x].get_map_coordinate_y()][map_data[y][x].get_map_coordinate_x()];}
	void link_adjacent_tiles(int x, int y);
	void generate_graph();
	const std::string END_OF_MAP = "EOM";
	const std::string END_OF_ROW = "EOR";
	void measurement();
	void center_pos(unsigned int wnd_width,  unsigned int wnd_height);
	void link_portals();
	std::vector<std::vector<Block> > map_data;
	std::vector<Block*> portals;
	std::vector<Block*> destinations;
	std::vector<Block*> intersections;
	std::vector<sf::Vector2i> _ghost_house;
	sf::Vector2i _pacman_init_pos;
	std::string parse_next_block(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end);
	sf::Vector2i parse_next_coordinate(const std::string& map_str, std::size_t& pos_begin, std::size_t& pos_end);
	sf::Vector2i _map_dimension;
	sf::Vector2i _block_size;
	sf::Vector2i _topleft;
	sf::Vector2f _scale;

	void load_map(std::ifstream &file, float h_scale, float v_scale);
	void register_ghost_house(std::ifstream &file);
	int _house_index[6];
};