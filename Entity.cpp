#include "Entity.h"

#include "Texture.h"
#include "Level.h"
#include "RenderWindow.h"


void Entity::draw_to(RenderWindow &targetRenderer) {
    targetRenderer.draw(texture, &frame, rect);
    targetRenderer.draw(rect);
}

void Entity::react_to_overlapping(const Rectangle& otherRect) {
    switch (currentMoveDirection) {
        case Direction::down:
            rect.set_y(otherRect.y() + otherRect.h());
            hitTop();
            break;
        case Direction::right:
            rect.set_x(otherRect.x() - rect.w());
            hitRight();
            break;
        case Direction::up:
            rect.set_y(otherRect.y() - rect.h());
            hitBottom();
            break;
        case Direction::left:
            rect.set_x(otherRect.x() + otherRect.w());
            hitLeft();
            break;
        default:
            break;
    }
}


void Entity::move(Level& level) {
    double xs = get_xspeed();
    double ys = get_yspeed();


    rect.set_x(rect.x() + xs);
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


    rect.set_y(rect.y() + ys);
    if (ys > 0) {
        currentMoveDirection = Direction::up;
    }
    else if (ys < 0) {
        currentMoveDirection = Direction::down;
    }
    else {
        currentMoveDirection = Direction::none;
    }
    level.check_collision(*this);

    did_move();
}

