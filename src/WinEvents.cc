#include "window.hh"

void Window::draw(sf::RenderWindow& window) 
{
    window.clear();
    Block block("13");
    //window.draw(_background->get_sprite());
    //window.draw(block.get_sprite());
    if (_cursor->get_visible()) {
        window.draw(_cursor->get_sprite());
    }
    _map->draw(window);
    window.display();
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
        break;
    default:
        break;
    }
}