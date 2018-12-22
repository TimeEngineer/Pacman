#include "image.hh" 

Image::Image(std::string file_path)
{
    load_image(file_path);
}


void Image::load_image(std::string file_path)
{
    sf::Vector2u size;
    _texture.loadFromFile(file_path);
	_sprite.setTexture(_texture);
    size = _texture.getSize();
    _width = size.x;
    _height = size.y;
    
}
void Image::set_position(int x, int y) { 
	_x = x;
	_y = y;
	_sprite.setPosition(sf::Vector2f(float(x),float(y)));
}
void Image::set_scale(float scaleWidth, float scaleHeight) {
	_scaleWidth = scaleWidth;
	_scaleHeight = scaleHeight;
	_sprite.setScale(sf::Vector2f(scaleWidth, scaleHeight));
}