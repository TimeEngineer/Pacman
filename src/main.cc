#include <SFML/Graphics.hpp>
#include "./Window/window.hh"
#include <thread>
#include <iostream>
/* RESOLUTION tested
1920 x 1080
1366 x 768
1280 x 800
*/
void foo()
{
    std::cout<<"Thread1" << std::endl;
}
void bar()
{
    std::cout<<"Thread2" << std::endl;
}
int main() {
    //std::thread first(foo);
    //std::thread second(bar);
    Window window(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height);
    window.launch();

    return 0;
}