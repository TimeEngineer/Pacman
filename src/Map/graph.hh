#pragma once
#include <vector>
#include <list>
#include "./Map/block.hh"
#include "./Map/edge.hh"
#include "./Map/vertex.hh"



class Graph{
public:
    Graph();
    virtual ~Graph(){};
    void generate(std::vector<Block*> &intersections);
    void associate();
    void shortest_route(Block &departure, Block &arrival);
    void prev();
    void next();
    
    const Block& get_prev_block() const {return *prev_block;}
    const Block& get_cur_block() const {return *cur_block;}
    const Block& get_next_block() const {return *next_block;}
    const Block& get_prev_intersection() const {return *prev_intersection;}
    const Block& get_cur_intersection() const {return *cur_intersection;}
    const Block& get_next_intersection() const {return *next_intersection;}
protected:
    std::vector<Edge> _edges;
    std::vector<Vertex> _vertices;
private:
    static const int INFINITY = 0xFFFFFFFF;
    int shortest_route(Block &departure, Block &arrival, int weight);
    
    Graph(const Graph&) {} // Protect copy constructor
    void operator =(const Graph&) {} // Protect assignment
    bool _lock;
    Block *prev_block;
    Block *prev_intersection;
    Block *cur_block;
    Block *cur_intersection;
    Block *next_block;
    Block *next_intersection;
	std::vector<struct Vertex::Path> _shortest_paths;
};