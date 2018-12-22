#pragma once
#include <SFML/Graphics.hpp>

class Image {
public:
    Image(std::string file_path);
    Image() {};
    virtual ~Image() {};
	sf::Sprite get_sprite() const {return _sprite;}
	void load_image(std::string file_path);
	void set_position(int x, int y);
	void set_scale(float scaleWidth, float scaleHeight);
	void set_size(int x, int y, float scaleWidth, float scaleHeight) {
		set_position(x,y); 
		set_scale(scaleWidth, scaleHeight);
	}

	std::size_t get_width() const {return _width;}
	std::size_t get_height() const {return _height;}
	int get_x() const {return _x;}
	int get_y() const {return _y;}
	float get_scaleWidth() const {return _scaleWidth;}
	float get_scaleHeight() const {return _scaleHeight;}
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	float _scaleWidth;
	float _scaleHeight;
	int _x;
	int _y;
	std::size_t _width;
	std::size_t _height;
};