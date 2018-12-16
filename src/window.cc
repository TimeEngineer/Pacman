#include "window.hh"

Window::Window(unsigned int width, unsigned int high) {
	this->width = width;
	this->high = high;
}

Window::~Window() {}

void menu_escape(sf::RenderWindow& window) {
    window.close();
}
void scores_escape(Background& background, Cursor& cursor) {
    background.set_sprite(bMENU);
    cursor.set_visible(true);
}
void switch_escape(sf::RenderWindow& window, Background& background, Cursor& cursor) {
    switch (background.get_token()) {
        case bMENU:
            menu_escape(window);
            break;
        case bSCORES:
            scores_escape(background, cursor);
            break;
        default:
            break;
    }
}

void menu_return(sf::RenderWindow& window, Background& background, Cursor& cursor) {
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
}
void scores_return(Background& background, Cursor& cursor) {
    background.set_sprite(bMENU);
    cursor.set_visible(true);
}
void switch_return(sf::RenderWindow& window, Background& background, Cursor& cursor) {
    switch (background.get_token()) {
        case bMENU:
            menu_return(window, background, cursor);
            break;
        case bSCORES:
            scores_return(background, cursor);
            break;
        default:
            break;
    }
}

void menu_up(Cursor& cursor) {
    if (cursor.get_y() > 500.f) {
        cursor.set_y(cursor.get_y() - 69.f);
    }
}
void switch_up(Background& background, Cursor& cursor) {
    switch (background.get_token()) {
        case bMENU:
            menu_up(cursor);
            break;
        default:
            break;
    }
}

void menu_down(Cursor& cursor) {
    if (cursor.get_y() < 776.f) {
        cursor.set_y(cursor.get_y() + 69.f);
    }
}
void switch_down(Background& background, Cursor& cursor) {
    switch (background.get_token()) {
        case bMENU:
            menu_down(cursor);
            break;
        default:
            break;
    }
}

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
                            switch_escape(window, background, cursor);
                            break;
                        case sf::Keyboard::Return:
                            switch_return(window, background, cursor);
                            break;
                        case sf::Keyboard::Up:
                            switch_up(background, cursor);
                            break;
                        case sf::Keyboard::Down:
                            switch_down(background, cursor);
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