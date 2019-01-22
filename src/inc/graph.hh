#pragma once
#include <vector>
#include <list>
#include "block.hh"
#include "edge.hh"
#include "vertex.hh"



class Graph{
public:
    Graph();
    virtual ~Graph(){};
    void generate(std::vector<Block*> &intersections);
    void associate();
    std::vector<struct Vertex::Path> shortest_route(const Block &departure, const Block &arrival);
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
    static const int INFINITY = 0xFFFF;
    int shortest_route(Vertex &departure, Vertex &arrival, int weight, int min_weight);
    Vertex *find_vertex(const Block &block);
    //int shortest_route(Block &departure, const Vertex &arrival, int weight, int min_weight);
    
    Graph(const Graph&):_cst_edges(_edges),_cst_vertices(_vertices) {} // Protect copy constructor
    void operator =(const Graph&) {} // Protect assignment
    bool _lock;
    Block *prev_block;
    Block *prev_intersection;
    Block *cur_block;
    Block *cur_intersection;
    Block *next_block;
    Block *next_intersection;
	std::vector<struct Vertex::Path> _shortest_paths;

public:
    const std::vector<Edge> &_cst_edges;
    const std::vector<Vertex> &_cst_vertices;
};