#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hh"
#include <string>

class Item : public Entity {
    public:
        Item(std::string file_path):
            Entity(file_path){}
        virtual ~Item() {};
        virtual void destroy() {};

        virtual EntityID get_entity_id() const {return EntityID::Item;}
        void draw(sf::RenderWindow& window) {
            if(get_visible())
                window.draw(_anim.get_sprite());
        }
        void set_visible(bool is_visible) {_anim.set_visible(is_visible);}
        bool get_visible() {return _anim.get_visible();}
};
