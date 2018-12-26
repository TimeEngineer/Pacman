#pragma once
#include <SFML/Graphics.hpp>

class Image {
public:
	//constructors
    Image(std::string file_path, bool transparent = false, sf::Color transparent_color = sf::Color(0,0,0));
    Image(bool transparent = false, sf::Color transparent_color = sf::Color(0,0,0)): _scale(1.0f), 
																					 _visible(true),
																					 _transparent(transparent), 
																					 _transparent_color(transparent_color) {};
    virtual ~Image() {};
	void load_image(std::string file_path);

	void reload();
	void turn_clockwise();
	// setters
	void set_offset(int offset_x, int offset_y);
	void set_position(int x, int y);
	void set_scale(float scaleWidth, float scaleHeight);
	void set_scale(float scale);
	void set_visible(bool visible);
	void set_size(int x, int y, float scaleWidth, float scaleHeight);
	void set_x(int x);
	void set_y(int y);
	void set_offset_x(int offset_x);
	void set_offset_y(int offset_y);
	void set_texture(const sf::Texture &texture);
	void set_angle(float angle);
	void set_frame_rect(const sf::IntRect &rectangle);
	//getters
	sf::Sprite get_sprite() const {return _sprite;}
	bool get_visible() {return _visible;}
	std::size_t get_width() const {return _width;}
	std::size_t get_height() const {return _height;}
	int get_x() const {return _x;}
	int get_y() const {return _y;}
	float get_scale() const {return _scale;}
	float get_scale_width() const {return _scale_width;}
	float get_scale_height() const {return _scale_height;}
	int get_offset_x() const {return _offset_x;}
	int get_offset_y() const {return _offset_y;}
	float get_angle() const {return _angle;}
	sf::Texture get_texture() const {return _texture;}
	sf::IntRect get_frame_rect() const {return _sprite.getTextureRect();};
	virtual void enable_origin_at_center();
	void set_origin(float x, float y);
private:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
	float _scale_width;
	float _scale_height;
	float _scale;
	float _angle;
	int _x;
	int _y;
	int _offset_x;
	int _offset_y;
	std::size_t _width;
	std::size_t _height;
	bool _visible;
	bool _transparent;
	sf::Color _transparent_color;
protected:
	sf::Texture load_texture(std::string file_path);
};