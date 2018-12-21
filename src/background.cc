#include "background.hh"

Background::Background(unsigned int width, unsigned int height, Woption option) {
    texture.loadFromFile("./DataBase/Images/Fonds/menu.png");

    // texture size : 420x460
    sprite.setTexture(texture);
    if (option == MEDIUM) {
    	int sprite_x = (width-840)>>1;
    	int sprite_y = (height-920)>>1;
	    sprite.setPosition(sf::Vector2f(float(sprite_x),float(sprite_y)));
	    sprite.setScale(sf::Vector2f(2.f, 2.f));
    }
    else {
    	int sprite_x = (width-420)>>1;
    	int sprite_y = (height-460)>>1;
    	sprite.setPosition(sf::Vector2f(float(sprite_x),float(sprite_y)));
    	sprite.setScale(sf::Vector2f(1.f, 1.f));
    }

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