#include "window.hh"

Window::Window(unsigned int width, unsigned int high) {
	this->width = width;
	this->high = high;
}

Window::~Window() {}

void Window::launch() {
	// Init
	sf::RenderWindow window(sf::VideoMode(width, high), "Pacman !", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

   	Background background(width, high);
    Cursor cursor(width, high);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::Up:
                            if (cursor.get_y() > 500.f) {
                                cursor.set_y(cursor.get_y() - 69.f);
                            }
                            break;
                        case sf::Keyboard::Down:
                            if (cursor.get_y() < 776.f) {
                                cursor.set_y(cursor.get_y() + 69.f);
                            }
                            break;
                        case sf::Keyboard::Return:
                            switch ((int(cursor.get_y())-500)/69) {
                                case JOUER:
                                    break;
                                case SCORES:
                                	background.set_sprite(bSCORES);
                                	cursor.set_visible(false);
                                    break;
                                case OPTIONS:
                                    break;
                                case CREDITS:
                                    break;
                                case QUITTER:
                                    window.close();
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        window.clear();
        window.draw(background.get_sprite());
        if (cursor.get_visible()) {
        	window.draw(cursor.get_sprite());
        }
        window.display();
    }
}