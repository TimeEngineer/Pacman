#include "routed.hh"

void Routed::set_path(const std::vector<sf::Vector2i>& vpath) {
	_vpath = vpath;
	_index = 0;
}

bool Routed::next() {
	if(_index < static_cast<int>(_vpath.size()))
		_index++;
	return true;
}