#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hh"
#include <string>

class Item : public Entity {
    public:
        Item(std::string file_path):
            Entity(file_path, 1){}
        virtual ~Item() {};
        virtual void destroy() {};

        virtual EntityID get_entity_id() const {return EntityID::Item;}
        void draw(sf::RenderWindow& window) {window.draw(_anim.get_sprite());}
};
