#pragma once
class Entity {
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
    Entity(){}
    ~Entity(){}
    virtual void destroy() = 0;
    void set_map_x(int map_x) {_map_x = map_x;}
    void set_map_y(int map_y) {_map_y = map_y;}
    int get_map_x() const {return _map_x;}
    int get_map_y() const {return _map_y;}
    virtual Entity::EntityID get_entity_id() const = 0;
protected: 
    int _map_x;
    int _map_y;
private:
    Entity::EntityID _entity_id;
};