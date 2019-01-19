#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "block.hh"
#include "vertex.hh"
#include "edge.hh"

class AutoRouted {
public:
	AutoRouted(){}
	~AutoRouted(){}
	void set_path(std::vector<struct Vertex::Path> _path);
	
	bool prev();
	bool next();
	bool step(bool bUp, Block *&front, Block *&back);
	bool synchro(sf::Vector2i pos);
	bool synchro(int x, int y);
	sf::Vector2i get_prev_block() const {return prev_block->get_map_coordinate();}
	sf::Vector2i get_cur_block() const {return cur_block->get_map_coordinate();}
	sf::Vector2i get_next_block() const {return next_block->get_map_coordinate();}
	sf::Vector2i get_prev_intersection() const {return prev_intersection->get_map_coordinate();}
	sf::Vector2i get_cur_intersection() const {return cur_intersection->get_map_coordinate();}
	sf::Vector2i get_next_intersection() const {return next_intersection->get_map_coordinate();}
private:
	int _nb_blocks;
	int _nb_paths;
	int _index_block;
	int _index_path;
	std::vector<struct Vertex::Path> _paths;
	std::vector<struct Vertex::Path>::iterator _vertex_it;
	std::vector<Block *>::iterator _edge_it;
	Edge *_cur_edge;
	bool _reversed;
	Block *prev_block;
	Block *prev_intersection;
	Block *cur_block;
	Block *cur_intersection;
	Block *next_block;
	Block *next_intersection;
};