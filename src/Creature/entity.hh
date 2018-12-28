#pragma once
#include <SFML/Graphics.hpp>
#include "./Graphics/image.hh"
#include "./Map/mapped.hh"

class Entity : public Mapped{
public:
	enum class EntityID {Pacman = 0x01,
					 Ghost0 = 0x02,
					 Ghost1 = 0x04,
					 Ghost2 = 0x08, 
					 Ghost3 = 0x10,
					 Energizer = 0x20,
					 Dot = 0x30,
					 Fruit = 0x40,
					 Creature = 0x1F,
					 Item = 0xE0};
    friend int operator~(const Entity::EntityID operand)
    {
        return ~static_cast<int>(operand);
    }
    Entity(Image& image) : Mapped(image){}
    ~Entity(){}
    virtual void destroy() = 0;
    virtual Entity::EntityID get_entity_id() const = 0;
private:
    Entity::EntityID _entity_id;
};