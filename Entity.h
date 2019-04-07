#ifndef LEARNCPP_ENTITY_H
#define LEARNCPP_ENTITY_H


#include <SDL.h>
#include "Rectangle.h"

class Scene;
class RenderWindow;
class Texture;
class Level;


enum class Direction {
    none,
    up,
    right,
    down,
    left
};

class Entity {
public:
    Entity(const Texture& texture, const SDL_Rect& frame) : texture{texture}, frame{frame} {}
    void draw_to(RenderWindow& targetRenderer);

    const Rectangle& get_rectangle() { return rect; }

    void react_to_overlapping(const Rectangle& otherRect);

    void move(Level& level);
protected:
    Rectangle rect{0.0, 0.0, 0, 0};
    const SDL_Rect& frame;
    virtual void hitRight() {}
    virtual void hitLeft() {}
    virtual void hitBottom() {}
    virtual void hitTop() {}
    virtual double get_xspeed() { return 0; }
    virtual double get_yspeed() { return 0; }
    virtual void did_move() {}
private:
    const Texture& texture;
    Direction currentMoveDirection{Direction::none};
};




#endif //LEARNCPP_ENTITY_H
