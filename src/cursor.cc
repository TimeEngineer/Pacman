#include "cursor.hh"

Cursor::Cursor(unsigned int width, unsigned int height, Woption option) {
    texture.loadFromFile("./DataBase/Images/Divers/cursor.png");

    sprite.setTexture(texture);
    if (option == MEDIUM) {
    	x = float(((width-840)>>1) + 340);
    	y = float(((height-920)>>1) + 420);
    	sprite.setPosition(sf::Vector2f(x,y));
    	sprite.setScale(sf::Vector2f(2.f, 2.f));
    }
    else {
    	x = float(((width-420)>>1) + 170);
    	y = float(((height-460)>>1) + 210);
    	sprite.setPosition(sf::Vector2f(x,y));
    	sprite.setScale(sf::Vector2f(1.f, 1.f));	
    }
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