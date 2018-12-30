#include "./Map/vertex.hh"

void Vertex::add_path(Edge &edge, bool is_reversed)
{
    struct Vertex::Path path = {&edge, is_reversed};
    _paths.push_back(path);
}