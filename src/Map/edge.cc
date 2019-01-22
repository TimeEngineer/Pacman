#include "edge.hh"


Edge::Edge(Block &vertex_src) :
_vertices(2, NULL),
_weight(0)
{
    _vertices.front() = &vertex_src;
    traverse(_vertices.front());
}
Edge::Edge(const Edge& edge) :
_weight(edge._weight)
{
    _vertices = edge._vertices;
    _route = edge._route;
}

bool Edge::traverse(Block* node) {
    if(node->is_visited())
        return false;


    if (Block::is_intersection(*node)) {
        if(node != _vertices.front()) {
            _vertices.back() = node;
            return true;
        }
    }
    else {
		_route.push_back(node);
        _weight++;
        node->visit();
    }
    if (EAST(node) != NULL && !EAST(node)->is_visited() && EAST(node) != _vertices.front())
            if (traverse(EAST(node)))
               return true;
    if (WEST(node) != NULL && !WEST(node)->is_visited() && WEST(node) != _vertices.front())
            if(traverse(WEST(node)))
                return true;
    if (SOUTH(node) != NULL && !SOUTH(node)->is_visited() && SOUTH(node) != _vertices.front())
            if(traverse(SOUTH(node)))
                return true;
    if (NORTH(node) != NULL && !NORTH(node)->is_visited() && NORTH(node) != _vertices.front())
            if(traverse(NORTH(node)))
              return true;
    // Mark the first vertex as visited.
    node->visit();
    return true;
}

// For debugging purpose
std::ostream& operator<<(std::ostream& os, const Edge &edge) {
    os <<"(" << edge._vertices.front()->get_map_coordinate_x()  << " , " << edge._vertices.front()->get_map_coordinate_y() << ")* -> ";
    for (const auto &iter : edge._route)
        os <<"(" << iter->get_map_coordinate_x()  << " , " << iter->get_map_coordinate_y() << ") -> ";
    os <<"*(" << edge._vertices.back()->get_map_coordinate_x()  << " , " << edge._vertices.back()->get_map_coordinate_y() << ")";
    return os;
}
    //std::cout<<"Cst"<<std::endl;
//std::cout<< "Mark:" << _vertices.front()->is_visited() << std::endl;
    //std::cout<< "Vertice:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
    //std::cout<< "Route:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
//std::cout<<"East"<<std::endl;
//std::cout<<"West"<<std::endl;
//std::cout<<"South"<<std::endl;
//std::cout<< "Mark" << std::endl;
//std::cout<<"North"<<std::endl;
//std::cout<< "Vertice:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
//std::cout<< "Route:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
//std::cout<<"North" << NORTH(node)->get_map_coordinate_x() << " , "<<NORTH(node)->get_map_coordinate_y() <<std::endl;
