#include "image.hh" 
#include <iostream>

Image::Image(std::string file_path) : 
_visible(true)
{
    load_image(file_path);	
}


void Image::load_image(std::string file_path)
{
    sf::Vector2u size;
    if(!_texture.loadFromFile(file_path)) {
		std::cerr<< "Invalid image." << std::endl;
		exit(0);
	}
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
void Image::set_scale(float scale) {
	_scale = scale;
	set_scale(_scale, _scale);
}
void Image::set_scale(float scaleWidth, float scaleHeight) {
	_scale_width = scaleWidth;
	_scale_height = scaleHeight;
	if(_scale_width == _scale_height)
		_scale = _scale_height;
	_sprite.setScale(sf::Vector2f(scaleWidth, scaleHeight));
}
void Image::set_visible(bool visible) 
{
	_visible = visible;
}
void Image::set_size(int x, int y, float scaleWidth, float scaleHeight) 
{
	set_position(x,y); 
	set_scale(scaleWidth, scaleHeight);
}
void Image::set_x(int x) 
{
	set_position(x, _y);
}
void Image::set_y(int y) 
{
	set_position(_x, y);
}