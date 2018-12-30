#include "graph.hh"

Graph::Graph() : _lock(false)
{

}
void Graph::generate(std::vector<Block*> &intersections)
{
	if(_lock)
		return;
	for (const auto& iter : intersections) {
		_vertices.push_back(*iter);
		while(!iter->is_visited()) {
			Edge edge(*iter);
			if(edge.get_weight() > 0)
				_edges.push_back(edge);
		}
	}
	_lock = true;
}
void Graph::associate()
{
	bool is_v1_found = false, is_v2_found = false;
	if(!_lock) 
		return;
	for (auto& edge_iter : _edges) {

		for(auto & vertex_iter :Graph::_vertices) {
			if(is_v1_found && is_v2_found) break;

			if(vertex_iter.get_vertex_block() == *edge_iter.get_vertices().front()) {
				vertex_iter.add_path(edge_iter, false);
				is_v1_found = true;
			}
			else if(vertex_iter.get_vertex_block() == *edge_iter.get_vertices().back()) {
				vertex_iter.add_path(edge_iter, true);
				is_v2_found = true;
			}
		}

	}
}

void  Graph::shortest_route(Block &departure, Block &arrival)
{
	int weight;
	if(departure == arrival)
		return;

		


}

int  Graph::shortest_route(Block &departure, Block &arrival, int weight)
{
	return 0;
}
    