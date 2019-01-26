#pragma once
#include <vector>
#include <list>
#include "block.hh"
#include "vertex.hh"
#include "edge.hh"

class Routed {
public:
    Routed(){}
    ~Routed(){}
    void set_path(const std::vector<sf::Vector2i>& vpath);

    const std::vector<sf::Vector2i>& get_path() const {return _vpath;}

    bool next();
    sf::Vector2i get_cur_pos() const {return _vpath[_index];}
private:
    int _index;
    std::vector<sf::Vector2i> _vpath;
};