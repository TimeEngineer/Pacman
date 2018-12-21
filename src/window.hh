#pragma once
#include <SFML/Graphics.hpp>
#include "background.hh"
#include "menu.hh"
#include "cursor.hh"
#include "woption.hh"

class Window {
	public:
		Window(unsigned int width, unsigned int height);
		~Window();
		void launch();
	private:
		unsigned int width;
		unsigned int height;
};