#include "Entity.h"

#include "Texture.h"
#include "Level.h"
#include "RenderWindow.h"


void Entity::draw_to(RenderWindow &targetRenderer) {
    SDL_Rect dest{static_cast<int>(rect.x), static_cast<int>(rect.y), frame.w, frame.h};
    targetRenderer.draw(texture, &frame, &dest);
    targetRenderer.draw(rect);
}

void Entity::react_to_overlapping(const Rectangle& otherRect) {
    switch (currentMoveDirection) {
        case Direction::up:
            rect.y = otherRect.y + otherRect.h;
            hitTop();
            break;
        case Direction::right:
            rect.x = otherRect.x - rect.w;
            hitRight();
            break;
        case Direction::down:
            rect.y = otherRect.y - rect.h;
            hitBottom();
            break;
        case Direction::left:
            rect.x = otherRect.x + otherRect.w;
            hitLeft();
            break;
        default:
            break;
    }
}


void Entity::move(Level& level) {
    double xs = get_xspeed();
    double ys = get_yspeed();


    rect.x += xs;
    if (xs > 0) {
        currentMoveDirection = Direction::right;
    }
    else if (xs < 0) {
        currentMoveDirection = Direction::left;
    }
    else {
        currentMoveDirection = Direction::none;
    }
    level.check_collision(*this);


    rect.y += ys;
    if (ys > 0) {
        currentMoveDirection = Direction::down;
    }
    else if (ys < 0) {
        currentMoveDirection = Direction::up;
    }
    else {
        currentMoveDirection = Direction::none;
    }
    level.check_collision(*this);

    did_move();
}

