#pragma once
#include <SFML/Graphics.hpp>
#include "image.hh"
#include "resources.hh"
#include "entity.hh"


class Block : public Image{
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
	static const std::size_t block_width = 24;
	static const std::size_t block_height = 24;
	unsigned char get_block_id() const {return _block_id;}
	Block::Status get_status() const {return _status;}
	void set_cor_x(int cor_x);
	void set_cor_y(int cor_y);
	int get_cor_x();
	int get_cor_y();
	void determine_status(int block_id);
	static const int MAX_PORTAL_NUMBERING = 8;
	static const int MAX_PORTAL = 4;
	static const int EMPTY_BLOCK_ID = 0;
private:
	unsigned char _block_id;
	Block::Status _status;
	bool isPortal;
	int _cor_x;
	int _cor_y;
};