#pragma once
#include <iostream>
#include <string>
#include "creature.hh"
#include "resources.hh"

class Pacman : public Creature {
	public:
	    Pacman(float scale);
	    ~Pacman();
	    void destroy();
	    virtual EntityID get_entity_id() const { return EntityID::Pacman;}
	    virtual void set_orientation(Creature::Orientation orientation);
	    void set_scene(int index_scene) {_anim.set_scene(index_scene);}
	    
	private:
	    typedef Pacman_Sprite::PACMAN_TYPE TYPE;
	    typedef Pacman_Sprite::PACMAN_ANIM ANIM;
};