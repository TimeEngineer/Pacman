#include "pacman.hh"

Pacman::Pacman(float scale) :
Creature(_default_path + _pacman_path, _pacman_frames),
_score(0)
{
    _anim.new_cut(TYPE::LIVE, 0, 4);
    _anim.new_cut(TYPE::DEAD, 4, 25);
    _anim.set_scene(TYPE::LIVE);
    _anim.set_scale(scale, scale);
}

Pacman::~Pacman() {}

void Pacman::destroy() {}

// Rotate Pacman
void Pacman::set_orientation(Creature::Orientation orientation) {
    sf::Vector2f scale = _anim.get_scale();
    scale.x = abs(scale.x);
    scale.y = abs(scale.y);
    switch(orientation) {
        case Orientation::Left :
            _anim.set_angle(0.0f);
            _anim.set_scale(-scale.x, scale.y);
            break;
        case Orientation::Right :
            _anim.set_angle(0.0f);
            _anim.set_scale(scale.x, scale.y);
            break;
        case Orientation::Bottom :
            _anim.set_angle(0.0f);
            _anim.set_scale(-scale.x, -scale.y);
            _anim.set_angle(270.0f);
            break;
        case Orientation::Top :
            _anim.set_angle(0.0f);
            _anim.set_scale(-scale.x, scale.y);
            _anim.set_angle(90.0f);
            break;
    }
    _orientation = orientation;
}
