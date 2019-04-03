#ifndef LEARNCPP_ENTITY_H
#define LEARNCPP_ENTITY_H


#include <SDL.h>
#include "Rectangle.h"

class Scene;
class RenderWindow;
class Texture;


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

    void move_x();
    void move_y();
    const Rectangle& get_rectangle() { return rect; }

    void react_to_overlapping(const Rectangle& otherRect);
protected:
    Rectangle rect{0.0, 0.0, 0, 0};
    double xSpeed{0};
    double ySpeed{0};
    const SDL_Rect& frame;
private:
    const Texture& texture;
    Direction currentMoveDirection{Direction::none};
};




#endif //LEARNCPP_ENTITY_H
