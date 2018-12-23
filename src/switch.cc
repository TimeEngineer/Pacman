#include "window.hh"

void Window::switch_escape(sf::RenderWindow& window) {
    switch (_background->get_token()) {
        case bJEU:
        case bREGLES:
        case bSCORES:
        case bOPTIONS:
        case bCREDITS:
            _mode = DrawMode::Bg;
            _background->set_sprite(bMENU);
            _cursor->set_visible(true);
            break;
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
            _mode = DrawMode::Game;
            break;
        case bSCORES:
            break;
        default:
            break;
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
            _mode = DrawMode::Bg;
            _background->set_sprite(_options[sel]);
            _cursor->set_visible(false);
            break;
            /*_mode = DrawMode::Game;*/
            // Don't draw game screen until rules aren't read.
            

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