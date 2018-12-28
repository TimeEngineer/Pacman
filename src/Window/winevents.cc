#include "./Window/window.hh"
#include <functional>
void Window::draw(sf::RenderWindow& window) 
{
    window.clear();

    switch(_mode) {
        case DrawMode::Game :
           // _map->draw(window);
            _game->draw(window);
            break; 
        case DrawMode::Bg :
                _background->draw(window);
            if (_cursor->get_visible()) 
                _cursor->draw(window);
        break;
        default:
        break;
            
    }
    window.display();
}
void Window::timer(sf::Clock &clock)
{
    sf::Time chrono;
    chrono = clock.getElapsedTime();
    for(const auto &tmev : timer_events) {
        if(chrono.asMilliseconds() - tmev->timer.asMilliseconds() >= tmev->time_ms) 
        {
            std::__invoke(tmev->event, *_game);
            tmev->timer = clock.getElapsedTime();
        }
    }
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
        _game->move_pacman(key);
        break;
    default:
        break;
    }
}