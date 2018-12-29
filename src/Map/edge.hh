#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "./Map/block.hh"

class Edge{
public:
    Edge(Block *vertex_src);
    virtual ~Edge(){};

    bool traverse(Block* departure);
    std::list<Block*> get_vertices() const {return _vertices;}
    int get_weight() const {return weight;}
    std::vector<Block*> get_route() const {return _route;}
private:
    std::list<Block*> _vertices;
    std::vector<Block*> _route;
    int weight;
    void find_route();
};