#include "image.hh" 
#include <iostream>

Image::Image(std::string file_path) : 
_scale(1.0f),
_visible(true)
{
    load_image(file_path);	
}


sf::Texture Image::load_texture(std::string file_path)
{
	sf::Texture texture;	
    if(!texture.loadFromFile(file_path)) {
		std::cerr<< "Invalid image." << std::endl;
		exit(0);
	}
	return texture;
}
void Image::load_image(std::string file_path)
{
    sf::Vector2u size;
	_texture = load_texture(file_path);
	_sprite.setTexture(_texture);
    size = _texture.getSize();
    _width = size.x;
    _height = size.y;
    
}
void Image::set_position(int x, int y) { 
	_x = x;
	_y = y;
	_sprite.setPosition(sf::Vector2f(static_cast<float>(x + _offset_x),static_cast<float>(y + _offset_y)));
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
	set_scale(scaleWidth, scaleHeight);
	set_position(x,y); 
}
void Image::set_x(int x) 
{
	set_position(x, _y);
}
void Image::set_y(int y) 
{
	set_position(_x, y);
}
void Image::set_offset_x(int offset_x)
{
	_offset_x = offset_x;
}
void Image::set_offset_y(int offset_y)
{
	_offset_y = offset_y;
}
void Image::set_offset(int offset_x, int offset_y)
{
	_offset_x = offset_x;
	_offset_y = offset_y;
}
void Image::set_texture(sf::Texture texture) 
{
	_texture = texture;
}
void Image::reload() 
{
    sf::Vector2u size;
	_sprite.setTexture(_texture);
    size = _texture.getSize();
    _width = size.x;
    _height = size.y;

}
void Image::set_angle(float angle) 
{
	_angle = angle;
	_sprite.setRotation(_angle);
}
void Image::turn_clockwise()
{
	int angle = (static_cast<int>(_angle) + 90) % 360;
	_angle = static_cast<float>(angle); 
	set_angle(_angle);
}