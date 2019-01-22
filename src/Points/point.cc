#include "point.hh"

Point::Point(float scale) :
Item(_default_path + _point_path)
{
    //An animation with 1 frame. ()
    _anim.new_cut(0, 0, 1);
    _anim.set_scale(scale, scale);
}

Point::~Point() {}

void Point::destroy() {}
