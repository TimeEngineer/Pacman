#include "block.hh"

Block::Block(unsigned char block_id)
{
	std::string image_file;
	unsigned char block, type;
	block = block_id >> 4;
	type = block_id & 0xF;
	
	image_file = std::to_string(block);
	if(image_file.length() == 1)
		image_file = "0" + image_file;
	image_file += std::to_string(type);
	
	load_image(image_file);	
}