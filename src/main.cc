#include <SFML/Graphics.hpp>
#include "window.hh"

/* RESOLUTION tested
1920 x 1080
1366 x 768
1280 x 800
*/

int main() {
    Window window(1280,800);
    window.launch();
    return 0;
}