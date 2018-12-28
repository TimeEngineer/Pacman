#pragma once
#include <SFML/Graphics.hpp>

class Image {
public:
	//constructors
    Image(std::string file_path, bool transparent = false, sf::Color transparent_color = sf::Color(0,0,0));
    Image(bool transparent = false, sf::Color transparent_color = sf::Color(0,0,0)): _offset(0,0),
																					 _visible(true),
																					 _transparent(transparent), 
																					 _transparent_color(transparent_color)
																					 {
																					 };
    virtual ~Image() {};
	void load_image(std::string file_path);
	void reload();
	// setters
	void set_visible(bool visible);

	void set_position(const sf::Vector2i& pos);
	void set_position(int x, int y);
	void set_x(int x);
	void set_y(int y);

	void set_scale(const sf::Vector2f& scale);
	void set_scale(float h_scale, float v_scale);
	void set_pos_scale(int x, int y, float h_scale, float v_scale);
	void set_angle(float angle);

	void set_frame_rect(const sf::IntRect &rectangle);
	void set_frame_rect(int x, int y, int width, int height);

	void set_offset(const sf::Vector2i& _offset);
	void set_offset(int offset_x, int offset_y);
	void set_offset_x(int offset_x);
	void set_offset_y(int offset_y);
	//getters
	sf::Sprite get_sprite() const {return _sprite;}
	bool get_visible() const {return _visible;}
	sf::Vector2i get_size() const {return sf::Vector2i(get_width(), get_height());}
	int get_width() const {return static_cast<int>(_texture.getSize().x);}
	int get_height() const {return static_cast<int>(_texture.getSize().y);}
	sf::Vector2i  get_position() const {return sf::Vector2i(get_x(), get_y());}
	int get_x() const {return _pos.x;}
	int get_y() const {return _pos.y;}
	sf::Vector2f get_scale() const {return _sprite.getScale();}
	float get_vertical_scale() const {return _sprite.getScale().x;}
	float get_horizontal_scale() const {return _sprite.getScale().y;}
	sf::Vector2i get_offset() const {return _offset;}
	int get_offset_x() const {return _offset.x;}
	int get_offset_y() const {return _offset.y;}
	float get_angle() const {return _angle;}
	sf::Texture get_texture() const {return _texture;}
	sf::IntRect get_frame_rect() const {return _sprite.getTextureRect();};
	virtual void enable_origin_at_center();
	void set_origin(float x, float y);
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2i _offset;
	sf::Vector2i _pos;
	float _angle;
	bool _visible;
	bool _transparent;
	sf::Color _transparent_color;
protected:
	sf::Texture load_texture(std::string file_path);
};
	//void set_texture(const sf::Texture &texture);