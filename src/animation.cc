#include "animation.hh"
#include <iostream>

Animation::Animation(std::string image_path):
Image(image_path)
{
    _textures.push_back(get_texture());
}
Animation::~Animation()
{
    
}
void Animation::add_image(std::string image_path)
{
    sf::Texture texture = load_texture(image_path);
    _textures.push_back(texture);
}
void Animation::insert_image(std::size_t index, std::string image_path)
{
    sf::Texture texture = load_texture(image_path);
    _textures.insert(_textures.begin() + index, texture);
}
void Animation::next()
{
    if(++_current_index >= _length) {
        reset();
    }
    set_texture(_textures[_current_index]);
    reload();
}
void Animation::prev()
{
     if(static_cast<int>(_current_index) <= 0) {
        _current_index = _length;
    }
    set_texture(_textures[--_current_index]);
    reload();
}
void Animation::reset()
{
    _current_index = 0;
}