#pragma once
#include <vector>
#include <list>
#include "./Map/block.hh"
#include "./Map/edge.hh"

class Vertex{
public:
    struct Path {
        Edge* edge;
        bool is_reversed;
    }Path;
    Vertex(Block &_vertex_block) : _vertex_block(_vertex_block){};
    Vertex(const Vertex& v) : _vertex_block(v._vertex_block) {_paths = v._paths;}
    virtual ~Vertex(){}; 

    void add_path(Edge &_edge, bool is_reverse);
    Block& get_vertex_block() const {return _vertex_block;}
    const std::vector<struct Vertex::Path> &get_paths() const {return _paths;}
private:
    Block& _vertex_block;
    std::vector<struct Vertex::Path> _paths;
    
};