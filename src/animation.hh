#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "image.hh"
class Animation : public Image
{
public:
    Animation(){}
    Animation(std::string image_path);
    ~Animation();
    void add_image(std::string image_path);
    void insert_image(std::size_t index, std::string image_path);
    void next();
    void prev();
    void reset();

    std::size_t get_current_index() { return _current_index;}
    std::size_t get_length() {return _length;}
private:
    std::vector<sf::Texture> _textures;
    std::size_t _current_index;
    std::size_t _length;    
};