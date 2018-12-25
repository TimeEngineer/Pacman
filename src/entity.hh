class Entity {
public:
    Entity(){}
    ~Entity(){}
    virtual void destroy() = 0;
protected: 
    int _x;
    int _y;

};