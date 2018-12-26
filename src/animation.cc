#include "animation.hh"
#include <iostream>
#include <cstdlib>
Animation::Animation(std::string file_path, int nb_frames, bool transparent, sf::Color color):
Image(file_path, transparent, color), 
_nb_frames(nb_frames),
_scene_index(0),
_nb_scenes(1) 
{
    _frame_width = get_width() / nb_frames;
    _frame_height = get_height();
    set_frame_rect(sf::IntRect(0,0,_frame_width,_frame_height));
}
Animation::~Animation()
{
}
void Animation::new_cut(int id, int begin, int nb_frames)
{
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
void Animation::next()
{
    struct scene &sc = _scenes[_scene_index];
    
    if(++sc.index >= sc.nb_frames) {
        reset();
    }
    set_frame_rect(sf::IntRect(_frame_width * (sc.begin + sc.index), 0, _frame_width, _frame_height));
    

}
void Animation::prev()
{
    struct scene &sc = _scenes[_scene_index];
    
    if(--sc.index <= sc.begin) {
        sc.index = sc.end;
    }
    set_frame_rect(sf::IntRect(_frame_width * (sc.begin + sc.index),0,_frame_width,_frame_height));
}
void Animation::reset()
{
    struct scene &sc = _scenes[_scene_index];
    sc.index = 0;
}
void Animation::set_scene(int id)
{
    _scene_index = 0;
    for(const auto& iter : _scenes) {
        if(iter.id == id)
            break;
        ++_scene_index;
    }
}
void Animation::enable_origin_at_center()
{
    this->set_origin(static_cast<float>(_frame_width) / 2.f,
                     static_cast<float>(_frame_height) / 2.f);
}