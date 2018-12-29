#include "./Map/edge.hh"

Edge::Edge(Block &vertex_src) :
_vertices(2, NULL)
{
    _vertices.front()= &vertex_src;

}

