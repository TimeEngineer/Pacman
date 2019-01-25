#include "graph.hh"

Graph::Graph() : _lock(false),
_cst_edges(_edges),
_cst_vertices(_vertices)
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
}
void Graph::associate_map_and_graph() {
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

Vertex *Graph::find_vertex(const Block &block) {
	for(auto& vertex : _vertices) {
		if(vertex() == block)
			return &vertex;
	}
	return NULL;
}
int  Graph::shortest_route(Vertex &depart, Vertex &arrival, int weight, int min_weight) {
	Vertex *new_depart = NULL;
	//Back tracking
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

std::vector<struct Vertex::Path>& Graph::shortest_route(const Block &depart, const Block &arrival) {
	//int weight;
	Vertex *vertex_depart = find_vertex(depart);
	Vertex *vertex_arrival = find_vertex(arrival);

//	std::cout<< "Search : " <<(*vertex_depart)().map_coordinate_to_string() << "->" << (*vertex_arrival)().map_coordinate_to_string()<<std::endl;
	shortest_route(*vertex_depart, *vertex_arrival, 0, Graph::INFINITY);
	/*int weight = 0;
	for(auto &iter : _shortest_paths) {
		std::cout<< *iter.edge <<std::endl;
		weight += iter.edge->get_weight();
	}
	std::cout<< "Weight:" << weight <<std::endl;
	*/
	return _shortest_paths;
}
std::vector<struct Vertex::Path>& Graph::specified_route(const Block &depart, const Block &arrival) {
	Vertex *vertex_depart = find_vertex(depart);
	Vertex *vertex_arrival = NULL;
	
	for(const auto& path : vertex_depart->get_paths()) {
		Edge *edge = path.edge;
		vertex_arrival = find_vertex(*(!path.reversed ? edge->get_vertices().back() : edge->get_vertices().front()));
		if((*vertex_arrival)() == arrival) {
			_shortest_paths.clear();
			_shortest_paths.insert(_shortest_paths.begin(), path);
			break;
		}

	}
	std::cout << std::endl;
		
	return _shortest_paths;
}
void Graph::prev() {}
void Graph::next() {}
