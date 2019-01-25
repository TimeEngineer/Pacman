#include "block.hh"
#include <iostream>
Block::Block(const int block_id, int col, int row) :
Mapped(col, row),
_east_block(NULL),
_west_block(NULL),
_south_block(NULL),
_north_block(NULL),
_visited_vertex(false),
_visited_edge(false),
_linked(false),
_image()
{
	if(block_id == -1) {
		_status = Status::Empty;
		return;
	}
	this->set_image(_image);
	std::string image_file = std::to_string(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;

	_image.load_image(_default_path + "./Images/Carte/" + image_file + ".png");
	_block_id = block_id;
	determine_status(_block_id);
}
Block::Block(const std::string& block_id, int col, int row) :
Mapped( col, row),
_east_block(NULL),
_west_block(NULL),
_south_block(NULL),
_north_block(NULL),
_visited_vertex(false),
_visited_edge(false),
_linked(false),
_image()
{
	std::string image_file(block_id);
	this->set_image(_image);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	_image.load_image(_default_path + "./Images/Carte/" + image_file + ".png");
	_block_id = std::stoi(block_id);
	determine_status(_block_id);
}

void Block::determine_status(int block_id) {
	//if(block_id == 9)
	//	_status = Status::Filled;
	if (block_id <= MAX_PORTAL_NUMBERING) {
		if (block_id == 0 )
			_status = Status::Empty;
		else if(block_id % 2 == 0)
			_status = Status::Portal;
		else
			_status = Status::Gateway;
	}
	else if (block_id == 998) {
		_status = Status::Door;
	}
	else if (block_id == 999) {
		_status = Status::Intersection;
	}
	else {
		_status = Status::Filled;
	}

}
void Block::set_destination(Block &block) {
	if (_status == Status::Portal)
		_map_coordinate = block._map_coordinate;
}
void Block::draw(sf::RenderWindow& window) const {
	window.draw(_image.get_sprite());
}
void Block::set_adjacent_tiles(Block *east_block, Block* west_block, Block* south_block, Block* north_block) {
	_east_block = determine_path(east_block);
	_west_block = determine_path(west_block);
	_south_block = determine_path(south_block);
	_north_block = determine_path(north_block);
	_linked = true;
}
Block *Block::determine_path(Block *path_block) {
	if(path_block == NULL || is_wall(*path_block))
		return NULL;
	return path_block;
}
/*
void Block::set_visited(bool visited) {
	_visited = visited;
}*/

void Block::visit_edge() {
	_visited_edge = true;
}
void Block::unvisit_edge() {
	_visited_edge = false;
}
void Block::visit_vertex() {
	_visited_vertex = true;
}
void Block::unvisit_vertex() {
	_visited_vertex = false;
}
bool Block::operator==(Block& block) {
	return block.get_map_coordinate() == this->get_map_coordinate();
}
bool Block::operator!=(Block& block) {
	return block.get_map_coordinate() != this->get_map_coordinate();
}
bool Block::operator==(const Block& block) {
	return block.get_map_coordinate() == this->get_map_coordinate();
}
bool Block::operator!=(const Block& block) {
	return block.get_map_coordinate() != this->get_map_coordinate();
}
