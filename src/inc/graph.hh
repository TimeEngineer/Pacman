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
	void convert_intersections_to_vertices();
	const std::vector<sf::Vector2i>& shortest_route(const sf::Vector2i &depart, const sf::Vector2i &arrival);
	//const std::vector<sf::Vector2i>& shortest_route(const Block &depart, const Block &arrival);
	//const std::vector<sf::Vector2i> specified_route(const Block &depart, const Block &arrival);
	const std::vector<sf::Vector2i> specified_route(const sf::Vector2i &depart, const sf::Vector2i &arrival);
	const std::vector<Edge> &_cst_edges;
	const std::vector<Vertex> &_cst_vertices;
	
protected:
	std::vector<Edge> _edges;
	std::vector<Vertex> _vertices;
	
private:
	Graph(const Graph&):_cst_edges(_edges),_cst_vertices(_vertices) {} // Protect copy constructor
	void operator =(const Graph&) {} // Protect assignment

	static const int INFINITY = 0xFFFF;
	// Find the shortest route between departing point and arriving point:
	int shortest_route(Vertex &depart, Vertex &arrival, int weight, int min_weight);
	// Convert the path structure to the vector of coordinates:
	std::vector<sf::Vector2i> paths_to_coordinates(std::vector<struct Vertex::Path> &paths);
	// Find the corresponding vertex of the given block:
	Vertex *find_vertex(const Block &block);
	Vertex *find_vertex(const sf::Vector2i &pos);
	
	std::vector<std::vector<sf::Vector2i> > _vect_of_shortest_paths;
	std::vector<struct Vertex::Path> _shortest_paths;
	bool _lock;

};