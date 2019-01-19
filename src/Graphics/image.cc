#include "image.hh" 

Image::Image(std::string file_path, bool transparent, sf::Color transparent_color) :
_offset(0,0),
_visible(true),
_transparent(transparent), 
_transparent_color(transparent_color),
_file_path(file_path)
{
	//std::cout<<"new"<< std::endl;
    load_image(file_path);	
	//std::cerr<< file_path << std::endl;
}
Image::~Image() {}

Image::Image(const Image& image):
	_texture(image._texture),
	_sprite(image._sprite),
	_offset(image._offset),
	_pos(image._pos),
	_center(image._center),
	_angle(image._angle),
	_visible(image._visible),
	_transparent(image._transparent),
	_transparent_color(image._transparent_color),
	_file_path(image._file_path),
	_center_origin(image._center_origin)
{

	//std::cout<<"New Constructor"<< std::endl;
	//	_sprite.setTexture(_texture);
	//std::cerr<< _file_path << std::endl;
	load_image(image._file_path);
	/*if(_center_origin) {
		set_origin(_center.x,_center.y);
	}
	set_position(_pos);
	set_scale(image.get_scale());
	set_frame_rect(image._sprite.getTextureRect());
	set_angle(_angle);*/
}

sf::Texture Image::load_texture(std::string file_path) {
	sf::Texture texture;	
	sf::Image image;
    if(!image.loadFromFile(file_path)) {
		std::cerr<< "Invalid image." << std::endl;
		exit(0);
	}
	_file_path = file_path;
	if(_transparent)
		image.createMaskFromColor(_transparent_color, 0);

	texture.loadFromImage(image);
	return texture;
}

void Image::set_frame_rect(const sf::IntRect &rectangle) {
	_sprite.setTextureRect(rectangle);
}
void Image::set_frame_rect(int x, int y, int width, int height) {
	_sprite.setTextureRect(sf::IntRect(x, y, width,height));
}
void Image::load_image(std::string file_path) {
    sf::Vector2u size;
	_texture = load_texture(file_path);
	reload();
}
void Image::set_position(const sf::Vector2i&  pos) { 
	_pos = pos;
	_sprite.setPosition(static_cast<float>(_pos.x + _offset.x + _center.x), static_cast<float>(_pos.y + _offset.y + _center.y));
}
void Image::set_position(int x, int y) { 
	set_position(sf::Vector2i(x, y));
}
void Image::set_scale(const sf::Vector2f&  scale) {
	set_scale(scale.x, scale.y);
}
void Image::set_scale(float h_scale, float v_scale) {
	_sprite.setScale(h_scale,v_scale);
	_center.x = static_cast<int>(_sprite.getOrigin().x * abs(h_scale));
	_center.y = static_cast<int>(_sprite.getOrigin().y * abs(v_scale));
}
void Image::set_visible(bool visible) {
	_visible = visible;
}
void Image::set_pos_scale(int x, int y, float h_scale, float v_scale)  {
	set_scale(h_scale, v_scale);
	set_position(x, y); 
}
void Image::set_x(int x)  {
	set_position(x, _pos.y);
}
void Image::set_y(int y)  {
	set_position(_pos.x, y);
}
void Image::set_offset_x(int offset_x) {
	_offset.x = offset_x;
	set_offset(_offset);
}
void Image::set_offset_y(int offset_y) {
	_offset.y = offset_y;
	set_offset(_offset);
}
void Image::set_offset(int offset_x, int offset_y) {
	//set_offset(offset_x, offset_y);
	_offset.x = offset_x;
	_offset.y = offset_y;
	set_position(_pos);
}
void Image::set_offset(const sf::Vector2i& offset) {
	_offset = offset;
	set_offset(_offset.x, _offset.y);
}
/*
void Image::set_texture(const sf::Texture &texture) 
{
	_texture = texture;
}*/
void Image::reload()  {
	_sprite.setTexture(_texture);

}
void Image::enable_origin_at_center() {
	_center_origin = true;
	set_origin(static_cast<float>(_texture.getSize().x) / 2.f, static_cast<float>(_texture.getSize().y) / 2.f);
}
void Image::set_origin(float x, float y) {
	_sprite.setOrigin(x, y);
	_center.x = static_cast<int>(x) * _sprite.getScale().x;
	_center.y = static_cast<int>(y) * _sprite.getScale().y;
}
void Image::set_angle(float angle) {
	_angle = angle;
	_sprite.setRotation(_angle);
}