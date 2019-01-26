#include "graph.hh"

Graph::Graph() : 
_cst_edges(_edges),
_cst_vertices(_vertices),
_vect_of_shortest_paths(1,std::vector<sf::Vector2i>(0, sf::Vector2i(-1,-1))),
_lock(false)
{}

void Graph::generate(std::vector<Block*> &intersections) {
	if(_lock)
		return;
	int last_n;
	for (const auto& iter : intersections) {
		_vertices.push_back(Vertex(*iter));
		
		last_n = 0;
		while(!iter->is_visited_vertex()) {
			Edge edge(*iter);
			if(edge.get_weight() > 0) {
				last_n++;
				_edges.push_back(edge);
			}
		}			
	}
	_lock = true;
	//std::cerr<<"end"<<std::endl;
}
void Graph::convert_intersections_to_vertices() {
	bool is_v1_found = false, is_v2_found = false;
	if(!_lock)
		return;
	for(auto & vertex_iter : _vertices)
		vertex_iter().unvisit_vertex();

	for (auto& edge_iter : _edges) {
		is_v1_found = false;
		is_v2_found = false;
		for(auto & vertex_iter : _vertices) {
			if(is_v1_found && is_v2_found) break;

			if(vertex_iter() == *edge_iter.get_vertices().front()) {
				vertex_iter.add_path(edge_iter, false);
				is_v1_found = true;
			}
			else if(vertex_iter() == *edge_iter.get_vertices().back()) {
				vertex_iter.add_path(edge_iter, true);
				is_v2_found = true;
			}
		}

	}
}

Vertex *Graph::find_vertex(const sf::Vector2i &pos) {
	for(auto& vertex : _vertices) {
		if(vertex().get_map_coordinate() == pos)
			return &vertex;
	}
	return NULL;

}
Vertex *Graph::find_vertex(const Block &block) {
	for(auto& vertex : _vertices) {
		if(vertex() == block)
			return &vertex;
	}
	return NULL;
}

std::vector<sf::Vector2i> Graph::paths_to_coordinates(std::vector<struct Vertex::Path> &paths) {
	std::vector<sf::Vector2i> vpath;
	sf::Vector2i front, back;
	
	for(const auto &iter_path : paths) {
		if (iter_path.reversed) {
			vpath.push_back(iter_path.edge->get_vertices().back()->get_map_coordinate());
			for(int i = iter_path.edge->get_route().size() - 1; i >=0 ; i--)
					vpath.push_back(iter_path.edge->get_route()[i]->get_map_coordinate());
			vpath.push_back(iter_path.edge->get_vertices().front()->get_map_coordinate());
		}
		else {
			vpath.push_back(iter_path.edge->get_vertices().front()->get_map_coordinate());
			for(int i = 0; i < static_cast<int>(iter_path.edge->get_route().size()); i++) 
				vpath.push_back(iter_path.edge->get_route()[i]->get_map_coordinate());
			vpath.push_back(iter_path.edge->get_vertices().back()->get_map_coordinate());
		}
	}
	return vpath;
}

int  Graph::shortest_route(Vertex &depart, Vertex &arrival, int weight, int min_weight) {
	Vertex *new_depart = NULL;
	
	int route_weight = 0;

	if(depart == arrival) {
		_shortest_paths.clear();
		return weight;
	}
	depart().visit_vertex();
	for(const auto& path : depart.get_paths()) {
		Edge *edge = path.edge;
		new_depart = find_vertex(*(path.reversed ? edge->get_vertices().front() : edge->get_vertices().back()));
		if(!(*new_depart)().is_visited_vertex() && weight + edge->get_weight() < min_weight) {
			route_weight = shortest_route(*new_depart, arrival, weight + edge->get_weight(), min_weight);
			if(min_weight > route_weight) {
				_shortest_paths.insert(_shortest_paths.begin(), path);
				min_weight = route_weight;
			}
		}

	}
	depart().unvisit_vertex();
	return min_weight;
}

const std::vector<sf::Vector2i>& Graph::shortest_route(const sf::Vector2i &depart, const sf::Vector2i &arrival)
{
	std::vector<sf::Vector2i> vpath, vpath_reverse;
	Vertex *vertex_depart = find_vertex(depart);
	Vertex *vertex_arrival = find_vertex(arrival);


	if(depart == arrival)
		return _vect_of_shortest_paths.front();
	// Look through registered shortest paths first.
	for(const auto &iter : _vect_of_shortest_paths) {
		if(iter.size() >= 2 && iter.front() == depart && iter.back() == arrival)
			return iter;
		
	}
	// If there isn't any shortest path registered, start searching :
	shortest_route(*vertex_depart, *vertex_arrival, 0, Graph::INFINITY);
	vpath = paths_to_coordinates(_shortest_paths);
	// Reversed the order and register it as well.
	for(const auto& iter : vpath){
		vpath_reverse.insert(vpath_reverse.begin(), iter);
	}
	_vect_of_shortest_paths.push_back(vpath_reverse);
	_vect_of_shortest_paths.push_back(vpath);
	return _vect_of_shortest_paths.back();
}
const std::vector<sf::Vector2i> Graph::specified_route(const sf::Vector2i &depart, const sf::Vector2i &arrival) {
	Vertex *vertex_depart = find_vertex(depart);
	Vertex *vertex_arrival = NULL;
	std::vector<sf::Vector2i> vpath;
	
	for(const auto& path : vertex_depart->get_paths()) {
		Edge *edge = path.edge;
		vertex_arrival = find_vertex(*(!path.reversed ? edge->get_vertices().back() : edge->get_vertices().front()));
		if((*vertex_arrival)().get_map_coordinate() == arrival) {
			_shortest_paths.clear();
			_shortest_paths.insert(_shortest_paths.begin(), path);
			break;
		}

	}
	vpath =  paths_to_coordinates(_shortest_paths);
		
	return vpath;
}

/*
const std::vector<sf::Vector2i>& Graph::shortest_route(const Block &depart, const Block &arrival) {
	std::vector<sf::Vector2i> vpath, vpath_reverse;
	Vertex *vertex_depart = find_vertex(depart);
	Vertex *vertex_arrival = find_vertex(arrival);
	sf::Vector2i depart_pos, arrival_pos;

	depart_pos = (*vertex_depart)().get_map_coordinate();
	arrival_pos = (*vertex_arrival)().get_map_coordinate();

	if(depart_pos == arrival_pos)
		return _vect_of_shortest_paths.front();
	// Look through registered shortest paths first.
	for(const auto &iter : _vect_of_shortest_paths) {
		if(iter.size() >= 2 && iter.front() == depart_pos && iter.back() == arrival_pos)
			return iter;
		
	}
	// If there isn't any shortest path registered, start searching :
	shortest_route(*vertex_depart, *vertex_arrival, 0, Graph::INFINITY);
	vpath = paths_to_coordinates(_shortest_paths);
	// Reversed the order and register it as well.
	for(const auto& iter : vpath){
		vpath_reverse.insert(vpath_reverse.begin(), iter);
	}
	_vect_of_shortest_paths.push_back(vpath_reverse);
	_vect_of_shortest_paths.push_back(vpath);
	
	
	//int weight;
	
	std::cout<< "Search : " <<(*vertex_depart)().map_coordinate_to_string() << "->" << (*vertex_arrival)().map_coordinate_to_string()<<std::endl;
	int weight = 0;
	for(auto &iter : _shortest_paths) {
		std::cout<< *iter.edge <<std::endl;
		weight += iter.edge->get_weight();
	}
	std::cout<< "Weight:" << weight <<std::endl;
	
	return _vect_of_shortest_paths.back();
}
*/