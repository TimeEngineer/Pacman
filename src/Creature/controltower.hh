#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "./Creature/ghost.hh"
#include "./Creature/pacman.hh"
#include "./Map/map.hh"
#include "resources.hh"

class ControlTower {
public:
    enum class Mode{Chase, Random, Ambush, Patrol, Scatter,Frightened};
    ControlTower(Map &map, Pacman &pacman, Blinky &blinky, Clyde &clyde, Inkey &inkey, Pinky &pinky):_map(map), 
                                                                                                     _pacman(pacman),
                                                                                                     _blinky(blinky), 
                                                                                                     _clyde(clyde),
                                                                                                     _inkey(inkey),
                                                                                                     _pinky(pinky){};
    ~ControlTower();
    void calculate(ControlTower::Mode mode);
    sf::Vector2i closest_intersection_to_pacman();
    void set_home(int x, int y) {_home = sf::Vector2i(x, y);}
    void set_home(sf::Vector2i &home) {_home = home;}
    std::vector<sf::Vector2i> get_path() {return _path;}
private:
    std::vector<sf::Vector2i> shortest_route(sf::Vector2i depart, sf::Vector2i destination);
    int distance_of_route(std::vector<sf::Vector2i> route);
    sf::Vector2i _home;
    std::vector<sf::Vector2i> _path;
    Map &_map; 
    Pacman &_pacman; 
    Blinky &_blinky; 
    Clyde &_clyde; 
    Inkey &_inkey; 
    Pinky &_pinky; 
};