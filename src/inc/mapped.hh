#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "image.hh"

class Mapped {
public:
	Mapped() {}
	Mapped(int x, int y) : _map_coordinate(x,y) {}
	Mapped(const Mapped &mapped) : _map_coordinate(mapped._map_coordinate) {}
	virtual ~Mapped() {}
	virtual void set_map_coordinate(sf::Vector2i map_coordinate);
	virtual void set_map_coordinate(int x, int y);
	virtual void set_map_coordinate_x(int x);
	virtual void set_map_coordinate_y(int y);

	virtual void set_screen_coordinate(sf::Vector2i screen_coordinate);
	virtual void set_screen_coordinate(int x, int y);
	virtual void set_screen_coordinate_x(int x);
	virtual void set_screen_coordinate_y(int y);
	
	virtual void set_screen_float_coordinate(sf::Vector2f screen_coordinate);
	virtual void set_screen_float_coordinate(float x, float y);
	virtual void set_screen_float_coordinate_x(float x);
	virtual void set_screen_float_coordinate_y(float y);

	virtual void set_offset(sf::Vector2i screen_coordinate);
	virtual void set_offset(int x, int y);

	void set_scale(sf::Vector2f scale);
	void set_scale(float h_scale, float v_scale);
	
	
	sf::Vector2i get_map_coordinate() const {return _map_coordinate;}
	int get_map_coordinate_x() const {return _map_coordinate.x;}
	int get_map_coordinate_y() const {return _map_coordinate.y;}
	sf::Vector2i get_screen_coordinate() const {return (*ptr_image).get_position();}
	sf::Vector2f get_screen_float_coordinate() const {return (*ptr_image).get_float_position();}
	int get_screen_coordinate_x() const {return (*ptr_image).get_x();}
	int get_screen_coordinate_float_x() const {return (*ptr_image).get_float_x();}
	int get_screen_coordinate_y() const {return (*ptr_image).get_y();}
	int get_screen_coordinate_float_y() const {return (*ptr_image).get_float_y();}
	

    sf::IntRect get_frame_rect() const {return (*ptr_image).get_frame_rect();};
	sf::Vector2f get_scale() const {return (*ptr_image).get_scale();}
	sf::Vector2i get_size() const {return (*ptr_image).get_size();}
	void set_image(Image& image) {ptr_image = &image;}
protected:
	Image get_image() {return *ptr_image;}
	Image *ptr_image;
	sf::Vector2i _map_coordinate;


};