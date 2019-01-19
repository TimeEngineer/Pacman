#include "reposize.hh"

sf::Vector2i calc_topleft(const sf::Vector2i& wnd_size, const sf::Vector2i& obj_size, const sf::Vector2f& scale) {
	sf::Vector2i topleft_pos;

	topleft_pos.x = (wnd_size.x - static_cast<int>(obj_size.x * scale.x)) >> 1;
	topleft_pos.y = (wnd_size.y - static_cast<int>(obj_size.y * scale.y)) >> 1;
	return topleft_pos;
}
sf::Vector2i calc_topleft(const sf::Vector2i& wnd_size, const sf::Vector2i& obj_size, const sf::Vector2i& scale) {
	sf::Vector2i topleft_pos;

	topleft_pos.x = (wnd_size.x - (obj_size.x * scale.x)) >> 1;
	topleft_pos.y = (wnd_size.y - (obj_size.y * scale.y)) >> 1;
	return topleft_pos;
}
sf::Vector2i calc_rescaled_size(const  sf::Vector2i& size, const sf::Vector2f& scale) {
	sf::Vector2i new_size;
	new_size.x = static_cast<int>(size.x * scale.x);
	new_size.y = static_cast<int>(size.y * scale.y);
	return new_size;
}