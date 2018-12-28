#pragma once
#include "./Creature/creature.hh"
#include "resources.hh"
#include <iostream>


class Pacman : public Creature
{
public:
    Pacman(float scale);
    ~Pacman();
    void destroy();
    virtual EntityID get_entity_id() const { return EntityID::Pacman;}
    virtual void set_orientation(Creature::Orientation orientation);
    
private:
    typedef Pacman_Sprite::PACMAN_TYPE TYPE;
    typedef Pacman_Sprite::PACMAN_ANIM ANIM;
};