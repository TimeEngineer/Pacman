#include "background.hh"

Background::Background(unsigned int width, unsigned int high) {
    texture.loadFromFile("./DataBase/Images/Fonds/menu.png");

    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(540.f,80.f));
    sprite.setScale(sf::Vector2f(2.f, 2.f));
}

Background::~Background() {}

sf::Sprite Background::get_sprite() const {
	return sprite;
}
background_option Background::get_token() const {
	return token;
}
void Background::set_sprite(background_option option) {
	switch (option) {
		case bMENU:
			texture.loadFromFile("./DataBase/Images/Fonds/menu.png");
			sprite.setTexture(texture);
			break;
		case bJEU:
			break;
		case bSCORES:
			texture.loadFromFile("./DataBase/Images/Fonds/scores.png");
			sprite.setTexture(texture);
			break;
		case bOPTIONS:
			break;
		case bCREDITS:
			break;
	}
}