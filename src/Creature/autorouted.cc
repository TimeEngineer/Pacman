#include "autorouted.hh"

void AutoRouted::set_path(std::vector<struct Vertex::Path> paths) {
	
	_paths = paths;

	_nb_paths = _paths.size();
	_index_path = 0;
	_index_block = 0;
	_nb_blocks = _paths[_index_path].edge->get_route().size();

	_reversed = _paths[_index_block].reversed;
	_cur_edge = _paths[_index_path].edge;
	if(_reversed) {
		_index_block = _nb_blocks - 1;
		prev_block = cur_block = cur_intersection = prev_intersection = _cur_edge->get_vertices().back();
		next_block = _cur_edge->get_route()[_index_block];
		next_intersection = _cur_edge->get_vertices().front();
	}
	else {
		_index_block = 0;
		prev_block = cur_block = cur_intersection = prev_intersection = _cur_edge->get_vertices().front();
		next_block = _cur_edge->get_route()[_index_block];
		next_intersection = _cur_edge->get_vertices().back();
	}
}
bool AutoRouted::step(bool bUp, Block *&front, Block *&back) {
	//first limit is between the vertex and the edge. ( route-> (F.L) -> intersection)
	//second limit is between the vertex and the vertex (route -> intersection -> (S.L) -> intersection -> route)
	int increment_step, first_limit, second_limit;
	increment_step = (bUp ? 1 : -1);
	first_limit = (bUp ? _nb_blocks : -1);
	second_limit = (bUp ? _nb_blocks + 1 : -2);
	_index_block += increment_step;

	if (_index_block == first_limit) {
		next_block = next_intersection;
	}
	else if (_index_block == second_limit) {
		if (_index_path < _nb_paths - 1) {
			_index_path++;
			_cur_edge = _paths[_index_path].edge;
			_nb_blocks = _paths[_index_path].edge->get_route().size();
			front = _cur_edge->get_vertices().front();
			back = _cur_edge->get_vertices().back();
		}
		else {
			_index_block = second_limit;
			return false;
		}
		_index_block = (bUp ? 0 : _nb_blocks - 1);
	}
	if (0 <= _index_block  && _index_block < _nb_blocks) {
		next_block = _cur_edge->get_route()[_index_block];
	}
	return true;
}
bool AutoRouted::next() {
	prev_block = cur_block;
	cur_block = next_block;
	
	if(_reversed) 
		step(false, next_intersection, prev_intersection);
	else
		step(true, prev_intersection, next_intersection);
	return true;
}
bool AutoRouted::prev() {	
	next_block = cur_block;
	cur_block = prev_block;
	return false;
}
    
		/*
		--_index_block;
		
		if(_index_block == -1) {
			next_block = next_intersection;
		}
		else if(_index_block == -2 ) {
			if(_index_path < _nb_paths - 1) {
				_index_path++;
				_cur_edge = _paths[_index_path].edge;
				_nb_blocks = _paths[_index_path].edge->get_route().size();
				prev_intersection =_cur_edge->get_vertices().back();
				next_intersection =_cur_edge->get_vertices().front();
			}
			else {
				_index_block = -2;
				return false;
			}
			_index_block = _nb_blocks - 1;
		}
		if(_index_block >= 0) { 
			next_block = _cur_edge->get_route()[_index_block];

		}
		*/