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
					 Filled = 0x00};
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

	Block(const unsigned char block_id);
	Block(const std::string& block_id);
	~Block(){};

	void determine_status(int block_id);
	void set_destination(const Block &block);

	unsigned char get_block_id() const {return _block_id;}
	Block::Status get_status() const {return _status;}

	bool is_portal() const { return borrow_coordinate;}
	bool is_portal_gateway() const { return lend_coordinate;}
	
	void draw(sf::RenderWindow &window);
	static const int MAX_PORTAL_NUMBERING = 8;
	static const int MAX_PORTAL = 4;
	static const int EMPTY_BLOCK_ID = 0;
private:
	Image _image;
	unsigned char _block_id;
	Block::Status _status;
	bool borrow_coordinate;
	bool lend_coordinate;
};