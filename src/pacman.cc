
#include "pacman.hh"
#include <string>

Pacman::Pacman(float scale) :
Creature(_default_path + _pacman_path, _pacman_frames)
{
    this->new_cut(TYPE::LIVE, 0, 4);
    this->new_cut(TYPE::DEAD, 4, 25);
    this->set_scene(TYPE::DEAD);
    /*const std::string live_pacman_path = _default_path + _pacman_paths[TYPE::LIVE];
    const std::string dead_pacman_path = _default_path + _pacman_paths[TYPE::DEAD];
    const int *live_index = _pacman_anim_index[TYPE::LIVE];
    const int *dead_index = _pacman_anim_index[TYPE::DEAD];

    //this->add_animation(live_pacman_path, _pacman_ext, live_index[ANIM::BEGIN], live_index[ANIM::END]);
   // this->new_animation_type(TYPE::DEAD);
    //this->add_animation(dead_pacman_path, _pacman_ext, dead_index[ANIM::BEGIN], dead_index[ANIM::END]);    
    //this->set_animation(TYPE::LIVE);*/
    this->set_scale(scale);
}


Pacman::~Pacman()
{}

void Pacman::destroy()
{

}