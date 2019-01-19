#include "mapped.hh"

void Mapped::set_map_coordinate(sf::Vector2i map_coordinate) {
	_map_coordinate = map_coordinate;	
}
void Mapped::set_map_coordinate(int x, int y) {
	set_map_coordinate(sf::Vector2i(x, y));
}
void Mapped::set_map_coordinate_x(int x) {
	_map_coordinate = sf::Vector2i(x, _map_coordinate.y);
}
void Mapped::set_map_coordinate_y(int y) {
	_map_coordinate = sf::Vector2i(_map_coordinate.x, y);
}
void Mapped::set_screen_coordinate(sf::Vector2i screen_coordinate) {
	(*ptr_image).set_position(screen_coordinate);
}
void Mapped::set_screen_coordinate(int x, int y) {
	(*ptr_image).set_position(x, y);
}
void Mapped::set_screen_coordinate_x(int x) {
	(*ptr_image).set_x(x);
}
void Mapped::set_screen_coordinate_y(int y) {
	(*ptr_image).set_y(y);
}
void Mapped::set_offset(sf::Vector2i screen_coordinate) {
	(*ptr_image).set_offset(screen_coordinate);
}
void Mapped::set_offset(int x, int y) {
	(*ptr_image).set_offset(x, y);
}
void Mapped::set_scale(sf::Vector2f scale) {
	(*ptr_image).set_scale(scale);
}
void Mapped::set_scale(float h_scale, float v_scale) {
	(*ptr_image).set_scale(h_scale, v_scale);
}