#include "window.hh"

Window::Window(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
}

Window::~Window() {}

void menu_escape(sf::RenderWindow& window) {
    window.close();
}
void rules_escape(Background& background, Cursor& cursor) {
    background.set_sprite(bMENU);
    cursor.set_visible(true);
}
void scores_escape(Background& background, Cursor& cursor) {
    rules_escape(background, cursor);
}
void switch_escape(sf::RenderWindow& window, Background& background, Cursor& cursor) {
    switch (background.get_token()) {
        case bMENU:
            menu_escape(window);
            break;
        case bREGLES:
            rules_escape(background, cursor);
            break;
        case bSCORES:
            scores_escape(background, cursor);
            break;
        default:
            break;
    }
}

void menu_return(sf::RenderWindow& window, Background& background, Cursor& cursor, Woption option, unsigned int height) {
    int condition;
    if (option == MEDIUM) {
        condition = (int(cursor.get_y())-(((height-920) >> 1) + 420))/69;
    }
    else {
        condition = int(((cursor.get_y()-float(((height-460) >> 1) + 210)))/34.5);
    }
    switch (condition) {
        case JOUER:
            background.set_sprite(bREGLES);
            cursor.set_visible(false);
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
        default:
            break;
    }
}
void scores_return(Background& background, Cursor& cursor) {
    background.set_sprite(bMENU);
    cursor.set_visible(true);
}
void rules_return(Background& background) {
    background.set_sprite(bJEU);
}
void switch_return(sf::RenderWindow& window, Background& background, Cursor& cursor, Woption option, unsigned int height) {
    switch (background.get_token()) {
        case bMENU:
            menu_return(window, background, cursor, option, height);
            break;
        case bREGLES:
            rules_return(background);
            break;
        case bSCORES:
            scores_return(background, cursor);
            break;
        default:
            break;
    }
}

void menu_up(Cursor& cursor, Woption option, unsigned int height) {
    if (option == MEDIUM) {
        if (cursor.get_y() > float(((height-920) >> 1) + 420)) {
            cursor.set_y(cursor.get_y() - 69.f);
        }
    }
    else {
        if (cursor.get_y() > float(((height-460) >> 1) + 210)) {
            cursor.set_y(cursor.get_y() - 34.5);
        }   
    }
}
void switch_up(Background& background, Cursor& cursor, Woption option, unsigned int height) {
    switch (background.get_token()) {
        case bMENU:
            menu_up(cursor, option, height);
            break;
        default:
            break;
    }
}

void menu_down(Cursor& cursor, Woption option, unsigned int height) {
    if (option == MEDIUM) {
        if (cursor.get_y() < float(((height-920) >> 1) + 696)) {
            cursor.set_y(cursor.get_y() + 69.f);
        }
    }
    else {
        if (cursor.get_y() < float(((height-460) >> 1) + 348)) {
            cursor.set_y(cursor.get_y() + 34.5);
        }   
    }
}
void switch_down(Background& background, Cursor& cursor, Woption option, unsigned int height) {
    switch (background.get_token()) {
        case bMENU:
            menu_down(cursor, option, height);
            break;
        default:
            break;
    }
}

void Window::launch() {
	// Init
	sf::RenderWindow window(sf::VideoMode(width, height), "Pacman !", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    Woption option;
    // texture size : 420x460
    if (width > 840 && height > 920) {
        option = MEDIUM;
    }
    else {
        option = SMALL;
    }

   	Background background(width, height, option);
    Cursor cursor(width, height, option);

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
                            switch_return(window, background, cursor, option, height);
                            break;
                        case sf::Keyboard::Up:
                            switch_up(background, cursor, option, height);
                            break;
                        case sf::Keyboard::Down:
                            switch_down(background, cursor, option, height);
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