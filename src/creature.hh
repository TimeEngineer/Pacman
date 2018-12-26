#pragma once
#include "entity.hh"
#include "sound.hh"
#include "animation.hh"
#include <vector>
#include <string>
#include <iostream>
class Creature : public Entity, public Animation 
{
public:
    enum class Orientation{Left, Right, Bottom, Top};
    Creature(std::string file_path, int nb_frames): Animation(file_path, nb_frames, true, sf::Color::Black),
                                     _lives(1),
                                     _speed(1.0f) {}
    virtual ~Creature() {};
    //virtual void playAnimation() = 0;
    virtual void destroy() {};
    void die() 
    {
        if(--_lives <= 0)
            destroy();
    } 
    void extra_life(){++_lives;}
    void set_lives(int lives) {_lives = lives;}
    void set_speed(float speed) {_speed = speed;}
    float get_speed() {return _speed;}
    int get_lives() {return _lives;}
    void add_sound(std::string file_path)
    {
        /*
        Sound sound(file_path);
        sounds.push_back(file_path);
        */
    }
    
    virtual EntityID get_entity_id() const {return EntityID::Creature;}
    virtual void set_orientation(Creature::Orientation orientation) {_orientation = orientation;}
    Creature::Orientation get_orientation() {return _orientation;}
protected: 
    Creature::Orientation _orientation;
    std::map<int, Sound> sounds;
    int _lives;
    float _speed;
};