
#include "pacman.hh"
#include <string>

Pacman::Pacman(float scale) :
Creature(_default_path + _pacman_path, _pacman_frames)
{
    this->new_cut(TYPE::LIVE, 0, 4);
    this->new_cut(TYPE::DEAD, 4, 25);
    this->set_scene(TYPE::LIVE);
    this->set_scale(scale);
}


Pacman::~Pacman()
{}

void Pacman::destroy()
{

}
void Pacman::set_orientation(Creature::Orientation orientation)
{
    float hscale = abs(get_scale_width()), vscale = abs(get_scale_height());
    switch(orientation) {
        case Orientation::Left :
            set_angle(0.0f);
            set_scale(-hscale,vscale);
            break;
        case Orientation::Right :
            set_angle(0.0f);
            set_scale(hscale,vscale);
            break;
        case Orientation::Bottom :
            set_angle(0.0f);
            set_scale(hscale,vscale);
            set_angle(90.0f);
            break;
        case Orientation::Top :
            set_angle(0.0f);
            set_scale(-hscale,-vscale);
            set_angle(90.0f);
            break;
    }
    _orientation = orientation;
}