#pragma once
#include <SFML/Graphics.hpp>
#include "./Graphics/animation.hh"
#include "./Map/mapped.hh"

class Entity : public Mapped{
public:
	enum class EntityID {Pacman = 0x01,
					 Ghost = 0x1E,
					 Blinky = 0x02,
					 Clyde = 0x04,
					 Inkey = 0x08, 
					 Pinky = 0x10,
					 Energizer = 0x20,
					 Dot = 0x30,
					 Fruit = 0x40,
					 Creature = 0x1F,
					 Item = 0xE0};
    friend int operator~(const Entity::EntityID operand)
    {
        return ~static_cast<int>(operand);
    }
    Entity(std::string file_path, int nb_frames) : Mapped(), _anim(file_path, nb_frames, true, sf::Color::Black) {this->set_image(_anim); enable_origin_at_center();}
    void enable_origin_at_center() {_anim.enable_origin_at_center();}
    ~Entity(){}
    virtual void destroy() = 0;
    virtual Entity::EntityID get_entity_id() const = 0;
protected:
	Animation _anim;
private:
    Entity::EntityID _entity_id;
};