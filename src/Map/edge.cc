#include "edge.hh"

Edge::Edge(Block &vertex_src) :
_vertices(2, NULL),
_weight(0)
{
	_vertices.front() = &vertex_src;
	traverse(_vertices.front());
	//std::cout<< "Mark:" << _vertices.front()->is_visited() << std::endl;
}
Edge::Edge(const Edge& edge) :
_weight(edge._weight)
{
	//std::cout<<"Cst"<<std::endl;
	_vertices = edge._vertices;
	_route = edge._route;
}

bool Edge::traverse(Block* node) {
	if(node->is_visited()) 
		return false;

	if (Block::is_intersection(*node)) {
		//std::cout<< "Vertice:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
		if(node != _vertices.front()) {
			_vertices.back() = node;
			return true;
		}
	}
	else {
		//std::cout<< "Route:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
		_route.push_back(node);
		_weight++;
		node->visit();
	}
	//std::cout<<"East"<<std::endl;
	if (EAST(node) != NULL && !EAST(node)->is_visited() && EAST(node) != _vertices.front()) 
			if (traverse(EAST(node)))
			   return true;
	//std::cout<<"West"<<std::endl;
	if (WEST(node) != NULL && !WEST(node)->is_visited() && WEST(node) != _vertices.front()) 
			if(traverse(WEST(node)))
				return true;
	//std::cout<<"South"<<std::endl;
	if (SOUTH(node) != NULL && !SOUTH(node)->is_visited() && SOUTH(node) != _vertices.front()) 
			if(traverse(SOUTH(node)))
				return true;          
	//std::cout<<"North"<<std::endl;
	if (NORTH(node) != NULL && !NORTH(node)->is_visited() && NORTH(node) != _vertices.front()) 
			if(traverse(NORTH(node)))
			  return true;
	// Mark the first vertex as visited.
	node->visit();
	//std::cout<< "Mark" << std::endl;
	return true;
}
std::ostream& operator<<(std::ostream& os, const Edge &edge) {
	os <<"(" << edge._vertices.front()->get_map_coordinate_x()  << " , " << edge._vertices.front()->get_map_coordinate_y() << ")* -> ";
	for (const auto &iter : edge._route) 
		os <<"(" << iter->get_map_coordinate_x()  << " , " << iter->get_map_coordinate_y() << ") -> ";
	os <<"*(" << edge._vertices.back()->get_map_coordinate_x()  << " , " << edge._vertices.back()->get_map_coordinate_y() << ")";
	return os;
}
//std::cout<< "Vertice:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
	//std::cout<< "Route:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
	//std::cout<<"North" << NORTH(node)->get_map_coordinate_x() << " , "<<NORTH(node)->get_map_coordinate_y() <<std::endl;