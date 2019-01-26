#pragma once
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
        void set_score(int score) {_score = 0;}
        void add_score(int score) {_score += score;}
        int get_score() {return _score;}
    private:
        int _score;
        typedef Pacman_Sprite::PACMAN_TYPE TYPE;
        typedef Pacman_Sprite::PACMAN_ANIM ANIM;
};
