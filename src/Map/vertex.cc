#include "vertex.hh"

void Vertex::add_path(Edge &edge, bool reversed) {
	struct Vertex::Path path = {&edge, reversed};
	_paths.push_back(path);
}
bool Vertex::operator==(Vertex &vertex) {
	return _vertex_block == vertex._vertex_block;
}
bool Vertex::operator!=(Vertex &vertex) {
	return _vertex_block != vertex._vertex_block;
}