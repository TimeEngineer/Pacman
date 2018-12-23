#include "window.hh"    
#include <iostream>
// background texture size : 420x460
#define BG_WIDTH Background::bg_width
#define BG_HEIGHT Background::bg_height
Window::Window(unsigned int width, unsigned int height) 
{
	_width = width;
	_height = height;
    _scale = ((_width <= BG_WIDTH && _height <= BG_HEIGHT) ? SMALL_SCALE : MEDIUM_SCALE);
    _background = new Background(_width, _height, _scale);
    _cursor = new Cursor(_width, _height, _scale, 0, 0, 4);

}

Window::~Window() 
{
    delete _background;
    delete _cursor;
}

void Window::launch() {
	// Init
	sf::RenderWindow window(sf::VideoMode(_width, _height), "Pacman !", sf::Style::Fullscreen);
    window.setFramerateLimit(60);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    key_pressed(window, event.key.code); 
                    break;
                default:
                    break;
            }   
        }
        draw(window); //WinEvents.cc
    }
}

void Window::menu_selected(sf::RenderWindow& window)
{
    int sel = _cursor->get_selection();
    switch (sel) {
        case JOUER:
        case SCORES:
        case OPTIONS:
        case CREDITS:
            _background->set_sprite(_options[sel]);
            _cursor->set_visible(false);
            break;
        case QUITTER:
            window.close();
            break;
        default:
            break;
    }
}
void Window::move_cursor(sf::Keyboard::Key dir) {
    _cursor->move((sf::Keyboard::Up == dir ? Cursor::Direction::Up : Cursor::Direction::Down));
}