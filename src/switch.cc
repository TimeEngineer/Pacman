#include "window.hh"

void Window::switch_escape(sf::RenderWindow& window) {
    switch (_background->get_token()) {
        case bREGLES:
        case bSCORES:
        case bOPTIONS:
        case bCREDITS:
            _background->set_sprite(bMENU);
            _cursor->set_visible(true);
        default:
            window.close();
            break;
    }
}

void Window::switch_arrowkey(sf::RenderWindow& window, sf::Keyboard::Key dir) {
    switch (_background->get_token()) {
        case bMENU:
            move_cursor(dir);
            break;
        default:
            break;
    }
}

void Window::switch_return(sf::RenderWindow& window) {
    switch (_background->get_token()) {
        case bMENU:
            menu_selected(window);
            break;
        case bREGLES:
            break;
        case bSCORES:
            break;
        default:
            break;
    }
}