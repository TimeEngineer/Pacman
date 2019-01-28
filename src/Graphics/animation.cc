#include "animation.hh"

Animation::Animation(std::string file_path, int nb_frames, bool transparent, sf::Color color):
Image(file_path, transparent, color), 
_nb_frames(nb_frames),
_scene_index(0),
_nb_scenes(1),
_loop(true)
{
	//Divide images into frames.
	_frame_width = get_width() / nb_frames;
	_frame_height = get_height();
	set_frame_rect(0,0,_frame_width,_frame_height);
}
Animation::~Animation() {}

// Register indexes of animations within an image.
// Ex) divide an image into two animation : pacman alive and pacman dead.
void Animation::new_cut(int id, int begin, int nb_frames) {
	if(begin + nb_frames > _nb_frames) {
		std::cerr<<"too many frames."<<std::endl;
		exit(0);
	}
	struct scene sc;
	sc.id = id;
	sc.begin = begin;
	sc.end = begin + (nb_frames - 1);
	sc.index = 0;
	sc.nb_frames = nb_frames;
	_scenes.push_back(sc);
	++_nb_scenes;
}
// Show the next frame of animation
void Animation::next() {
	struct scene &sc = _scenes[_scene_index];
	
	++sc.index;
	if(sc.index >= sc.nb_frames) {
		if(_loop)
			reset();
		else
			return;
	}
	set_frame_rect(_frame_width * (sc.begin + sc.index), 0, _frame_width, _frame_height);
}
// Show the prev frame of animation
void Animation::prev() {
	struct scene &sc = _scenes[_scene_index];
	
	--sc.index;
	if(sc.index >= sc.nb_frames) {
		if(_loop)
			sc.index = sc.end;
		else
			return;
	}
	set_frame_rect(_frame_width * (sc.begin + sc.index),0,_frame_width,_frame_height);
}
// Reset the index of current animation
void Animation::reset() {
	struct scene &sc = _scenes[_scene_index];
	sc.index = 0;
}
// Change the animation.
void Animation::set_scene(int id) {
	_scene_index = 0;
	for(const auto& iter : _scenes) {
		if(iter.id == id)
			break;
		++_scene_index;
	}
	reset();
}
// Make sure that images rotate around its center so that it doesn't move.
void Animation::enable_origin_at_center() {
	this->set_origin(static_cast<float>(_frame_width) / 2.f,
					 static_cast<float>(_frame_height) / 2.f);
}