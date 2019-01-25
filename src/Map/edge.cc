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
//Recursive search in order to find the next path available to the neighboring vertex(node).
bool Edge::traverse(Block* node) {
    
    if(node->is_visited_vertex()) 
        return false;
    if (Block::is_intersection(*node)) {
        if(node != _vertices.front()) { // There is no looping edge.
            if(_weight++ == 0) //If intersection is adjecent, consider it an edge.
                node->visit_edge();

            _vertices.back() = node;
            return true;
        }
    }
    else {
        node->visit_edge();
		_route.push_back(node);
        _weight++;
    }
    if (EAST(node) != NULL && !EAST(node)->is_visited_edge() && EAST(node) != _vertices.front())
        if (traverse(EAST(node))) 
           return true;

    if (WEST(node) != NULL && !WEST(node)->is_visited_edge() && WEST(node) != _vertices.front())
        if(traverse(WEST(node))) 
           return true;

    if (SOUTH(node) != NULL && !SOUTH(node)->is_visited_edge() && SOUTH(node) != _vertices.front())
            if(traverse(SOUTH(node))) 
                return true;

    if (NORTH(node) != NULL && !NORTH(node)->is_visited_edge() && NORTH(node) != _vertices.front()) 
        if(traverse(NORTH(node))) 
            return true;
    // Mark the first vertex as visited.
    node->visit_vertex();
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
bool Edge::operator ==(const Edge &edge) const
{
    if (this->get_vertices().front() == edge.get_vertices().front() && this->get_vertices().front() == edge.get_vertices().back())
        return true;
    else if (this->get_vertices().back() == edge.get_vertices().front() && this->get_vertices().back() == edge.get_vertices().back())
        return true;
    return false;
}
bool Edge::operator !=(const Edge &edge) const
{
    if (this->get_vertices().front() == edge.get_vertices().front() && this->get_vertices().front() == edge.get_vertices().back())
        return false;
    else if (this->get_vertices().back() == edge.get_vertices().front() && this->get_vertices().back() == edge.get_vertices().back())
        return false;
    return true;
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
/*static int i = 0;
    //std::cout<< "Front:" << _vertices.back()->get_map_coordinate_x() << " , " << _vertices.back()->get_map_coordinate_y() << std::endl;
    //std::cout<< i <<" Vertice:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
    //std::cout<< "Front:" << _vertices.front()->get_map_coordinate_x() << " , " << _vertices.front()->get_map_coordinate_y() << std::endl;
    i++;
        std::cout<<"Intersection"<<std::endl;
           std::cout<<"Back"<<std::endl;
               i--;
    std::cout<< "Route:" << node->get_map_coordinate_x() << " , " << node->get_map_coordinate_y() << std::endl;
    std::cout<<"East"<<std::endl;
    std::cout<<"West"<<std::endl;
    std::cout<<"South"<<std::endl;
    std::cout<<"North"<<std::endl;
    std::cout<< "Mark" << std::endl;

     */