#include "./Map/block.hh"
#include <iostream>
Block::Block(const int block_id, int col, int row) :
Mapped(_image, col, row),
_east_block(NULL),
_west_block(NULL),
_south_block(NULL),
_north_block(NULL)
{	
	std::string image_file = std::to_string(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	
	_image.load_image(_default_path + "./Images/Carte/" + image_file + ".png");	
	_block_id = block_id;
	determine_status(_block_id); 
}
Block::Block(const std::string& block_id, int col, int row) :
Mapped(_image, col, row),
_east_block(NULL),
_west_block(NULL),
_south_block(NULL),
_north_block(NULL)
{
	std::string image_file(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	_image.load_image(_default_path + "./Images/Carte/" + image_file + ".png");	
	_block_id = std::stoi(block_id);
	determine_status(_block_id); 
}

void Block::determine_status(int block_id)
{
	if (block_id <= MAX_PORTAL_NUMBERING) {
		if (block_id == 0 ) 
			_status = Status::Empty;
		else if(block_id % 2 == 0) 
			_status = Status::Portal;
		else 
			_status = Status::Gateway;
	}
	else if (block_id == 999) {
		_status = Status::Intersection;
	}
	else {
		_status = Status::Filled;
	}
		
}
void Block::set_destination(const Block& block)
{
	if (_status == Status::Portal) 
		_map_coordinate = block._map_coordinate;
}
void Block::draw(sf::RenderWindow& window)
{
	window.draw(_image.get_sprite());
}
void Block::set_adjacent_tiles(Block *east_block, Block* west_block, Block* south_block, Block* north_block)
{
	_east_block = east_block;
	_west_block = west_block;
	_south_block = south_block;
	_north_block = north_block;
}