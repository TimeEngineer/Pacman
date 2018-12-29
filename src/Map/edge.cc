#include "./Map/edge.hh"

Edge::Edge(Block *vertex_src) :
_vertices(2, NULL),
_weight(0)
{
    _vertices.front() = vertex_src;
    traverse(_vertices.front());
}

#define EAST(block) block->get_east_block()
#define WEST(block) block->get_west_block()
#define SOUTH(block) block->get_south_block()
#define NORTH(block) block->get_north_block()
bool Edge::traverse(Block* departure)
{
    if(departure->is_visited()) {
        return false;
    }
    if (Block::is_intersection(*departure)) {
        std::cout<< "Vertice:" << departure->get_map_coordinate_x() << " , " << departure->get_map_coordinate_y() << std::endl;
        if(departure != _vertices.front()) {
            _vertices.back() = departure;
            return true;
        }
    }
    else {
		std::cout<< "Route:" << departure->get_map_coordinate_x() << " , " << departure->get_map_coordinate_y() << std::endl;
        _route.push_back(departure);
        _weight++;
        departure->set_visited(true);
    }

    if (EAST(departure) != NULL && !EAST(departure)->is_visited() && EAST(departure) != _vertices.front()) 
        if(traverse(EAST(departure)))
            return true;
    
    if (WEST(departure) != NULL && !WEST(departure)->is_visited() && WEST(departure) != _vertices.front()) 
        if(traverse(WEST(departure)))
            return true;
    
    if (SOUTH(departure) != NULL && !SOUTH(departure)->is_visited() && SOUTH(departure) != _vertices.front()) 
        if(traverse(SOUTH(departure)))
            return true;
    
    if (NORTH(departure) != NULL && !NORTH(departure)->is_visited() && NORTH(departure) != _vertices.front()) 
        if(traverse(NORTH(departure)))
            return true;
    departure->set_visited(true);
    return true;
}