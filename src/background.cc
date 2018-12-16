#include "background.hh"

Background::Background(unsigned int width, unsigned int high) {
    texture.loadFromFile("./DataBase/Images/Fonds/menu.png");

    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(540.f,80.f));
    sprite.setScale(sf::Vector2f(2.f, 2.f));

    token = bMENU;
}

Background::~Background() {}

sf::Sprite Background::get_sprite() const {
	return sprite;
}
background_option Background::get_token() const {
	return token;
}
void Background::set_sprite(background_option option) {
	buffer.loadFromFile("./DataBase/Sounds/choice.wav");
	sound.setBuffer(buffer);
	sound.play();
	switch (option) {
		case bMENU:
			texture.loadFromFile("./DataBase/Images/Fonds/menu.png");
			break;
		case bREGLES:
			texture.loadFromFile("./DataBase/Images/Fonds/rules.png");
			break;
		case bJEU:
			texture.loadFromFile("./DataBase/Images/Fonds/basic_level.png");
			break;
		case bSCORES:
			texture.loadFromFile("./DataBase/Images/Fonds/scores.png");
			break;
		case bOPTIONS:
			break;
		case bCREDITS:
			break;
		default:
			break;
	}
	sprite.setTexture(texture);
	token = option;
}