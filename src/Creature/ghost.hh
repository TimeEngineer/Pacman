#pragma once
#include "./Creature/autorouted.hh"
#include "./Creature/creature.hh"
#include "./Map/map.hh"
#include "resources.hh"
#include <iostream>


class Ghost : public Creature, public AutoRouted
{
public:
    Ghost(std::string file_path, float scale);
    ~Ghost();
    void destroy();
    virtual EntityID get_entity_id() const { return EntityID::Ghost;}
    virtual void set_orientation(Creature::Orientation orientation);
    void set_scene();
    
protected:
    typedef Ghost_Sprite::GHOST_TYPE GHOST_TYPE;
    typedef Ghost_Sprite::GHOST_ORIENTATION GHOST_ORIENTATION;
    typedef Ghost_Sprite::GHOST_STATUS GHOST_STATUS;
    GHOST_ORIENTATION _anim_orientation;
    GHOST_STATUS _anim_status;
};

class Inkey : public Ghost
{
public:
    Inkey(float scale):Ghost(_default_path + _ghost_paths[GHOST_TYPE::INKEY], scale){}
    ~Inkey(){}
    virtual EntityID get_entity_id() const { return EntityID::Inkey;}
private:
};
class Clyde : public Ghost
{
public:
    Clyde(float scale):Ghost(_default_path + _ghost_paths[GHOST_TYPE::CLYDE], scale){}
    ~Clyde(){}
    virtual EntityID get_entity_id() const { return EntityID::Clyde;}
private:
};
class Blinky : public Ghost
{
public:
    Blinky(float scale):Ghost(_default_path + _ghost_paths[GHOST_TYPE::BLINKY], scale){}
    ~Blinky(){}
    virtual EntityID get_entity_id() const { return EntityID::Blinky;}
private:
};
class Pinky : public Ghost
{
public:
    Pinky(float scale):Ghost(_default_path + _ghost_paths[GHOST_TYPE::PINKY], scale){}
    ~Pinky(){}
    virtual EntityID get_entity_id() const { return EntityID::Pinky;}
private:
};