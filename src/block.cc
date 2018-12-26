#include "block.hh"
#include <iostream>
Block::Block(const unsigned char block_id)
{	
	std::string image_file = std::to_string(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	
	load_image(_default_path + "/Images/Carte/" + image_file + ".png");	
	_block_id = static_cast<unsigned char>(block_id);
	determine_status(_block_id); 
}
Block::Block(const std::string& block_id) 
{
	std::string image_file(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	load_image(_default_path + "/Images/Carte/" + image_file + ".png");	
	_block_id = static_cast<unsigned char>(std::stoi(block_id));
	determine_status(_block_id); 
}
void Block::set_cor_x(int cor_x) 
{
	_cor_x = cor_x;
}
void Block::set_cor_y(int cor_y) 
{
	_cor_y = cor_y;
}
int Block::get_cor_x() 
{
	return _cor_x;
}
int Block::get_cor_y() 
{
	return _cor_y;
} 
void Block::determine_status(int block_id)
{
	if (block_id <= MAX_PORTAL_NUMBERING) {
		if (block_id == 0 || block_id % 2 !=0 ) 
			_status = Status::Empty;
		else if(block_id % 2 == 0)
			_status = Status::Portal;
	}
	else {
		_status = Status::Filled;
	}
}