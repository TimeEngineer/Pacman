#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "./Map/block.hh"

class Edge{
public:
    Edge(Block &vertex_src);
    Edge(const Edge& edge);
    virtual ~Edge(){};

    void visit();
    void unvisit();

    friend std::ostream& operator<<(std::ostream& os, const Edge &edge);
    int get_weight() const {return _weight;}
    std::list<Block*> get_vertices() const {return _vertices;}
    std::vector<Block*> get_route() const {return _route;}
private:
    bool traverse(Block* node);
    std::list<Block*> _vertices;
    std::vector<Block*> _route;
    int _weight;
    bool _visited;
    void find_route();
};