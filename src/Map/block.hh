#pragma once
#include <SFML/Graphics.hpp>
#include "./Graphics/image.hh"
#include "./Creature/entity.hh"
#include "./Map/mapped.hh"
#include "resources.hh"


class Block: public Mapped {
public:
	enum class Status {Empty = 0xFF,
					 Portal = 0x01,
					 Filled = 0x00,
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

	Block(const int block_id, int col, int row);
	Block(const std::string& block_id, int col, int row);
	~Block(){};

	void draw(sf::RenderWindow &window);
	void determine_status(int block_id);

	void set_destination(const Block &block);
	void set_adjacent_tiles(Block *east_block, Block* west_block, Block* south_block, Block* north_block);
	void set_visited(bool visited);

	Block *get_east_block() const {return _east_block;}
	Block *get_west_block() const {return _west_block;}
	Block *get_south_block() const {return _south_block;}
	Block *get_north_block() const {return _north_block;}

	int get_block_id() const {return _block_id;}
	Block::Status get_status() const {return _status;}
	bool is_visited() const {return _visited;}
	bool is_linked() const {return _linked;}
	static bool is_wall(Block &block)  {return block.get_status() == Status::Filled;}
	static bool is_portal(Block &block)  {return block.get_status() == Status::Portal;}
	static bool is_gateway(Block &block)  {return block.get_status() == Status::Gateway;}
	static bool is_intersection(Block &block) {return block.get_status() == Status::Intersection;}
	sf::Vector2i operator()(int x, int y) const{return get_map_coordinate();}
	static const int MAX_PORTAL_NUMBERING = 8;
	static const int MAX_PORTAL = 4;
	static const int EMPTY_BLOCK_ID = 0;
private:
	Block *determine_path(Block *path_block);
	void operator=(const Block&){}
	Block *_east_block;
	Block *_west_block;
	Block *_south_block;
	Block *_north_block;
	bool _visited;
	bool _linked;
	Image _image;
	int _block_id;
	Block::Status _status;
};