#pragma once
#include <SFML/Graphics.hpp>
sf::Vector2i calc_topleft(const sf::Vector2i& wnd_size, const sf::Vector2i& obj_size, const sf::Vector2f& scale);
sf::Vector2i calc_topleft(const sf::Vector2i& wnd_size, const sf::Vector2i& obj_size, const sf::Vector2i& scale);
sf::Vector2i calc_rescaled_size(const  sf::Vector2i& size, const sf::Vector2f& scale);