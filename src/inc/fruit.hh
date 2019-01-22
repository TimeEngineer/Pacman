#pragma once
#include "item.hh"
#include "resources.hh"
#include <string>

class Fruit : public Item {
    public:
        Fruit(float scale, std::string option);
        Fruit(const Fruit &fruit);
        ~Fruit();
        void destroy();
        virtual EntityID get_entity_id() const {return EntityID::Fruit;}
    private:
        std::string _option;
};
