#pragma once
#include "item.hh"
#include "resources.hh"

class Energizer : public Item {
    public:
        Energizer(float scale);
        Energizer(const Energizer &energizer);
        ~Energizer();
        void destroy();
        virtual EntityID get_entity_id() const {return EntityID::Energizer;}
};
