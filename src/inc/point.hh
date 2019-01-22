#pragma once
#include "item.hh"
#include "resources.hh"

class Point : public Item {
    public:
        Point(float scale);
        Point(const Point &point);
        ~Point();
        void destroy();
        virtual EntityID get_entity_id() const {return EntityID::Dot;}
};
