#include "cursor.hh"

Cursor::Cursor(unsigned int width, unsigned int high) {
    texture.loadFromFile("./DataBase/Images/Divers/cursor.png");

    sprite.setTexture(texture);
    x = 880.f;
    y = 500.f;
    sprite.setPosition(sf::Vector2f(x,y));
    sprite.setScale(sf::Vector2f(2.f, 2.f));
    visible = true;
}

Cursor::~Cursor() {}

sf::Sprite Cursor::get_sprite() const {
	return sprite;
}
float Cursor::get_x() const {
	return x;
}
float Cursor::get_y() const {
	return y;
}
bool Cursor::get_visible() const {
	return visible;
}
void Cursor::set_sprite(sf::Sprite& s) {
	sprite = s;
}
void Cursor::set_x(float f) {
	x = f;
	sprite.setPosition(sf::Vector2f(x,y));
}
void Cursor::set_y(float f) {
	buffer.loadFromFile("./DataBase/Sounds/cursor.wav");
    sound.setBuffer(buffer);
    sound.play();
	y = f;
	sprite.setPosition(sf::Vector2f(x,y));
}
void Cursor::set_visible(bool b) {
	visible = b;
}