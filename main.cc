#include <SFML/Graphics.hpp>
#include "menu.hh"

int main() {
    // Init
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pacman !", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    sf::Sprite background;
    sf::Sprite indicator;

    // Menu
    sf::Texture menu;
    menu.loadFromFile("./DataBase/Images/Fonds/menu.png");
    // Cursor
    sf::Texture cursor;
    cursor.loadFromFile("./DataBase/Images/Divers/cursor.png");

    background.setTexture(menu);
    background.setPosition(sf::Vector2f(540.f,80.f));
    background.setScale(sf::Vector2f(2.f, 2.f));

    indicator.setTexture(cursor);
    float cursor_x = 880.f;
    float cursor_y = 500.f;
    indicator.setPosition(sf::Vector2f(cursor_x,cursor_y));
    indicator.setScale(sf::Vector2f(2.f, 2.f));

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
                            if (cursor_y > 500.f) {
                                cursor_y -= 69.f;
                                indicator.setPosition(sf::Vector2f(cursor_x,cursor_y));
                            }
                            break;
                        case sf::Keyboard::Down:
                            if (cursor_y < 776.f) {
                                cursor_y += 69.f;
                                indicator.setPosition(sf::Vector2f(cursor_x,cursor_y));
                            }
                            break;
                        case sf::Keyboard::Return:
                            switch ((int(cursor_y)-500)/69) {
                                case 0:
                                    break;
                                case 1:
                                    break;
                                case 2:
                                    break;
                                case 3:
                                    break;
                                case 4:
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
        window.draw(background);
        window.draw(indicator);
        window.display();
    }

    return 0;
}