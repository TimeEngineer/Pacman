#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "./Map/block.hh"

class Graph{
public:
    Graph(const std::vector<Block*> &vertices);
    virtual ~Graph(){};



private:
    Graph(const Graph&) {} // Protect copy constructor
    void operator =(const Graph&) {} // Protect assignment

    std::vector<Block*> &_vertices;
    std::vector<int> &_mark;
    bool lock;
    
};