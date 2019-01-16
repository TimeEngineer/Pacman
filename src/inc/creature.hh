#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hh"
#include "sound.hh"
#include "animation.hh"
#include <vector>
#include <string>
#include <iostream>
class Creature : public Entity
{
public:
    enum class Orientation{Left, Right, Bottom, Top};
    Creature(std::string file_path, int nb_frames):
                                     Entity(file_path, nb_frames),
                                     _lives(1),
                                     _speed(1.0f) { }
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
    void enable_origin_at_center() {_anim.enable_origin_at_center();}
    
    void draw(sf::RenderWindow& window) {window.draw(_anim.get_sprite());}
    void next_frame() { _anim.next(); }
    void prev_frame() { _anim.prev(); }
protected: 
    Creature::Orientation _orientation;
    std::map<int, Sound> sounds;
    int _lives;
    float _speed;
};