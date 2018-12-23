#include "block.hh"
#include <iostream>
Block::Block(const unsigned char block_id)
{	
	std::string image_file = std::to_string(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	
	load_image(_default_path + "/Images/Carte/" + image_file + ".png");	
	_block_id = static_cast<unsigned char>(block_id);
}
Block::Block(const std::string& block_id) 
{
	std::string image_file(block_id);
	while(image_file.length() < 3)
		image_file = "0" + image_file;
	load_image(_default_path + "/Images/Carte/" + image_file + ".png");	
	_block_id = static_cast<unsigned char>(std::stoi(block_id));
}