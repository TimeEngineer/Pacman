#include "window.hh"

void Window::draw(sf::RenderWindow& window) 
{
    window.clear();

    switch(_mode) {
        case DrawMode::Game :
           // _map->draw(window);
            game->draw(window);
            break; 
        case DrawMode::Bg :
            window.draw(_background->get_sprite());
    
            if (_cursor->get_visible()) 
                window.draw(_cursor->get_sprite());
        break;
        default:
        break;
            
    }
    window.display();
}
void Window::timer(sf::Clock &clock, bool &redraw)
{
    bool bRestartClock = true;
    
    redraw = game->animate_pacman(clock);
    if(redraw)
        clock.restart();
}

void Window::key_pressed(sf::RenderWindow& window, sf::Keyboard::Key key)
{
    //switch.cc
    switch (key)
    {
    case sf::Keyboard::Escape:
        switch_escape(window);
        break;
    case sf::Keyboard::Return:
        switch_return(window);
        break;
    case sf::Keyboard::Up:
    case sf::Keyboard::Down:
    case sf::Keyboard::Left:
    case sf::Keyboard::Right:
        switch_arrowkey(window, key);
        game->move_pacman(key);
        break;
    default:
        break;
    }
}