#include "./Map/block.hh"
#include <iostream>
Block::Block(const unsigned char block_id) :
Mapped(_image),
borrow_coordinate(false),
lend_coordinate(false)
{	
	std::string image_file = std::to_string(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	
	_image.load_image(_default_path + "./Images/Carte/" + image_file + ".png");	
	_block_id = static_cast<unsigned char>(block_id);
	determine_status(_block_id); 
}
Block::Block(const std::string& block_id) :
Mapped(_image),
borrow_coordinate(false),
lend_coordinate(false)
{
	std::string image_file(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	_image.load_image(_default_path + "./Images/Carte/" + image_file + ".png");	
	_block_id = static_cast<unsigned char>(std::stoi(block_id));
	determine_status(_block_id); 
}

void Block::determine_status(int block_id)
{
	if (block_id <= MAX_PORTAL_NUMBERING) {
		if (block_id == 0 ) 
			_status = Status::Empty;
		else if(block_id % 2 == 0) {
			_status = Status::Portal;
			borrow_coordinate = true;
		}
		else {
			_status = Status::Empty;
			lend_coordinate = true;
		}
	}
	else {
		_status = Status::Filled;
	}
}
void Block::set_destination(const Block& block)
{
	if (borrow_coordinate) {
		_map_coordinate = block._map_coordinate;
	}
}
void Block::draw(sf::RenderWindow& window)
{
	window.draw(_image.get_sprite());
}