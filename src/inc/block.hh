#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "image.hh"
#include "entity.hh"
#include "mapped.hh"
#include "resources.hh"


class Block: public Mapped {
public:
	enum class Status {Empty = 0xFF,
					 Portal = 0x1F,
					 Filled = 0x00,
					 Door = 0x1E, // Only ghost can pass.
					 Intersection = 0x1FF,
					 Gateway = 0x2FF};
	friend int operator&(const Block::Status operand1, const Entity::EntityID operand2)
	{
	    return static_cast<int>(operand1) & static_cast<int>(operand2);
	}
	friend int operator&(const Entity::EntityID operand1, const Block::Status operand2)
	{
	    return operand2 & operand1;
	}

	friend int operator|(const Block::Status operand1, const Entity::EntityID operand2)
	{
	    return static_cast<int>(operand1) | static_cast<int>(operand2);
	}
	friend int operator|(const Entity::EntityID operand1, const Block::Status operand2)
	{
	    return operand2 & operand1;
	}
	Block() :Mapped(),_east_block(NULL),
	_west_block(NULL),
	_south_block(NULL),
	_north_block(NULL),
	_visited_vertex(false),
	_visited_edge(false),
	_linked(true),
	 _image(),
	 _block_id(-1){
		this->set_image(_image);
	}

	Block(const int block_id, int col, int row);
	Block(const std::string& block_id, int col, int row);
	Block(const Block& block):
	Mapped(block),
	_west_block(block._west_block),
	_south_block(block._south_block),
	_north_block(block._north_block),
	_visited_vertex(block._visited_vertex),
	_visited_edge(block._visited_edge),
	_linked(block._linked),
	_image(block._image),
	 _block_id(block._block_id),
	 _status(block._status)
	 {
		this->set_image(_image);
	 }
	 
	~Block(){};

	void draw(sf::RenderWindow &window) const;
	void determine_status(int block_id);

	void set_destination(Block &block);
	void set_adjacent_tiles(Block *east_block, Block* west_block, Block* south_block, Block* north_block);
	void visit_vertex();
	void unvisit_vertex();
	void visit_edge();
	void unvisit_edge();
	Block *get_east_block() const {return _east_block;}
	Block *get_west_block() const {return _west_block;}
	Block *get_south_block() const {return _south_block;}
	Block *get_north_block() const {return _north_block;}
	std::string map_coordinate_to_string() {return " (" + std::to_string(_map_coordinate.x) + " , " + std::to_string(_map_coordinate.y) + ") ";}
	int get_block_id() const {return _block_id;}
	Block::Status get_status() const {return _status;}
	bool is_visited_vertex() const {return _visited_vertex;}
	bool is_visited_edge() const {return _visited_edge;}
	bool is_linked() const {return _linked;}
	static bool is_wall(Block &block)  {return block.get_status() == Status::Filled;}
	static bool is_portal(Block &block)  {return block.get_status() == Status::Portal;}
	static bool is_gateway(Block &block)  {return block.get_status() == Status::Gateway;}
	static bool is_intersection(Block &block) {return block.get_status() == Status::Intersection;}
	static bool is_door(Block &block)  {return block.get_status() == Status::Door;}

	
	bool is_wall() const {return _status == Status::Filled;}
	bool is_portal() const {return _status == Status::Portal;}
	bool is_gateway() const {return _status == Status::Gateway;}
	bool is_intersection() const {return _status == Status::Intersection;}
	bool is_door() const {return _status == Status::Door;}
	
	sf::Vector2i operator()(int x, int y) const{return get_map_coordinate();}
	static const int MAX_PORTAL_NUMBERING = 8;
	static const int MAX_PORTAL = 4;
	static const int EMPTY_BLOCK_ID = 0;
	static Block null_block;
	bool operator==(Block& block);
	bool operator!=(Block& block);
	bool operator==(const Block& block);
	bool operator!=(const Block& block);
private:
	Block *determine_path(Block *path_block);
	Block *_east_block;
	Block *_west_block;
	Block *_south_block;
	Block *_north_block;
	bool _visited_vertex;
	bool _visited_edge;
	bool _linked;
	Image _image;
	int _block_id;
	Block::Status _status;
};