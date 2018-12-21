#include <SFML/Graphics.hpp>
#include "window.hh"

/* RESOLUTION tested
1920 x 1080
1366 x 768
1280 x 800
*/

int main() {
    Window window(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height);
    window.launch();
    return 0;
}