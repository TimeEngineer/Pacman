#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "block.hh"

#define EAST(block) block->get_east_block()
#define WEST(block) block->get_west_block()
#define SOUTH(block) block->get_south_block()
#define NORTH(block) block->get_north_block()

class Edge{
public:
    Edge(Block &vertex_src);
    Edge(const Edge& edge);
    virtual ~Edge(){};
    bool operator ==(const Edge &edge) const;
    bool operator !=(const Edge &edge) const;
    

    friend std::ostream& operator<<(std::ostream& os, const Edge &edge);
    int get_weight() const {return _weight;}
    const std::list<Block*>& get_vertices() const {return _vertices;}
    const std::vector<Block*>& get_route() const {return _route;}
private:
    bool traverse(Block* node);
    std::list<Block*> _vertices;
    std::vector<Block*> _route;
    int _weight;
    void find_route();
};
