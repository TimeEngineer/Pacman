#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "woption.hh"
#include "autoposimage.hh"
#include "sound.hh"
#include "woption.hh"
#include "background.hh"
#include "database.hh"


class Cursor : public AutoPosImage, Sound {
	public:
		enum Direction {Up = 0, Down = 1};
		Cursor(unsigned int width, unsigned int height, float scale, int selection, int limit_min, int limit_max);
		~Cursor();
		void move(Direction dir);
		int get_selection() const {return _selection;}
		int get_limit_min() const {return _limit_min;}
		int get_limit_max() const {return _limit_max;}
		void set_limit_min(int limit_min);
		void set_limit_max(int limit_max);
	private:
		int _init_x;
		int _init_y;
		int _selection;
		int _limit_min;
		int _limit_max;
};