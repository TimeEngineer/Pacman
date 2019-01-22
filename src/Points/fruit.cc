#include "fruit.hh"

// "option = Images/Points/fruit.png"
Fruit::Fruit(float scale, std::string option) :
Item(_default_path + option)
{
    //An animation with 1 frame. ()
    _option = option;
    _anim.new_cut(0, 0, 1);
    _anim.set_scale(scale, scale);
}
Fruit::Fruit(const Fruit &fruit) :
Fruit(fruit._anim.get_scale().x, fruit._option)
{}

Fruit::~Fruit() {}

void Fruit::destroy() {}
