#include "energizer.hh"

Energizer::Energizer(float scale) :
Item(_default_path + _energizer_path)
{
    //An animation with 1 frame. ()
    _anim.new_cut(0, 0, 1);
    _anim.set_scale(scale, scale);
}
Energizer::Energizer(const Energizer &energizer) :
Energizer(energizer._anim.get_scale().x)
{}

Energizer::~Energizer() {}

void Energizer::destroy() {}
