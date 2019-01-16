#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "image.hh"
class Animation : public Image
{
public:
    struct scene {
        int id;
        int begin;  
        int end;  
        int index;
        int nb_frames;
    } scene;
    Animation(std::string file_path, 
             int nb_frames,
             bool transparent = false,
             sf::Color color = sf::Color::Black);
    ~Animation();
    void new_cut(int id, int begin, int nb_frames);
    void set_scene(int id);
    void next();
    void prev();
    void reset();
    unsigned int get_frame_width(){return _frame_width;}
    unsigned int get_frame_height(){return _frame_height;}

    std::vector<struct Animation::scene> get_scene() const {return _scenes;};
    std::size_t get_nb_scenes() const {return _nb_scenes;}
	virtual void enable_origin_at_center();
private:
    std::vector<struct Animation::scene> _scenes;
    int _nb_frames;
    std::size_t _scene_index;  
    std::size_t _nb_scenes;
    unsigned int _frame_width;
    unsigned int _frame_height;
};