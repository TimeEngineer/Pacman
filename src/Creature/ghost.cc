#include "ghost.hh"


//Set the animation scenes for ghosts.
Ghost::Ghost(std::string file_path,  float scale) :
Creature(file_path, 32)
{
    GHOST_STATUS status[3] = {GHOST_STATUS::LIVE,
                             GHOST_STATUS::BLUE,
                             GHOST_STATUS::DEAD};
    GHOST_ORIENTATION orientation[4] = {GHOST_ORIENTATION::LEFT,
                                        GHOST_ORIENTATION::RIGHT,
                                        GHOST_ORIENTATION::TOP,
                                        GHOST_ORIENTATION::BOTTOM};
    for (int index_stat = 0; index_stat < 3; index_stat++) {
        for (int index_ori = 0; index_ori < 4; index_ori++) {
            //std::cout << status[index_stat] + orientation[index_ori] << std::endl;
            _anim.new_cut(status[index_stat] | orientation[index_ori],
                         index_ori * 2, 2);
        }
    }
    _anim.set_scale(scale, scale);
}

Ghost::~Ghost() {}

void Ghost::destroy() {}
//Rotate ghost.
void Ghost::set_orientation(Creature::Orientation orientation) {
    switch(orientation) {
        case Orientation::Left :
            _anim_orientation = GHOST_ORIENTATION::LEFT;
            break;
        case Orientation::Right :
            _anim_orientation = GHOST_ORIENTATION::RIGHT;
            break;
        case Orientation::Bottom :
            _anim_orientation = GHOST_ORIENTATION::BOTTOM;
            break;
        case Orientation::Top :
            _anim_orientation = GHOST_ORIENTATION::TOP;
            break;
    }
    _anim.set_scene(GHOST_STATUS::LIVE | _anim_orientation);
    _orientation = orientation;
}
void Ghost::set_scene() {}
