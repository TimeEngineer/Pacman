#pragma once
#include "creature.hh"
#include "resources.hh"


class Pacman : public Creature
{
public:
    Pacman(float scale);
    ~Pacman();
    void destroy();
private:
    typedef Pacman_Sprite::PACMAN_TYPE TYPE;
    typedef Pacman_Sprite::PACMAN_ANIM ANIM;
};