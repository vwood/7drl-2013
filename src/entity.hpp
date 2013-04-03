#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
private:
    int x, y;
    Drawing *drawing;
    
public:
    Entity(Random &r, int x, int y);
    ~Entity();
    
};

#endif
