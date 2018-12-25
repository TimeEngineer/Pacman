#pragma once
#include "entity.hh"
#include "sound.hh"
#include "animation.hh"
#include <vector>
class Creature : public Entity, public Animation 
{
public:
    Creature():_lives(1), _speed(1.0f) {}
    virtual ~Creature() {};
    virtual void playAnimation() = 0;
    void destroy() = 0;
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
protected: 
    std::map<int, Sound> sounds;
    int _lives;
    float _speed;
};