#pragma once
#include <vector>
#include <list>
#include "block.hh"
#include "edge.hh"

class Vertex{
	public:
		struct Path {
			Edge* edge;
			bool reversed;
		}Path;
		Vertex(Block &_vertex_block) : _vertex_block(_vertex_block) {};
		Vertex(const Vertex& v) : _vertex_block(v._vertex_block) {_paths = v._paths;}
		virtual ~Vertex(){}; 

		void add_path(Edge &_edge, bool reverse);
		Block& get_vertex_block() const {return _vertex_block;}
		const std::vector<struct Vertex::Path> &get_paths() const {return _paths;}

		bool operator==(Vertex &vertex);
		bool operator!=(Vertex &vertex);
		Block& operator()() {return _vertex_block;}
	private:
		Block& _vertex_block;
		std::vector<struct Vertex::Path> _paths;
};