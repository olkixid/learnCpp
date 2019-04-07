#include "Entity.h"

#include "Texture.h"


void Entity::draw_to(RenderWindow &targetRenderer) {
    SDL_Rect dest{static_cast<int>(rect.x), static_cast<int>(rect.y), frame.w, frame.h};
    texture.draw_to(targetRenderer, &frame, &dest);
    rect.draw_to(targetRenderer);
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

void Entity::move_x() {
    rect.x += xSpeed;
    if (xSpeed > 0) {
        currentMoveDirection = Direction::right;
    }
    else if (xSpeed < 0) {
        currentMoveDirection = Direction::left;
    }
    else {
        currentMoveDirection = Direction::none;
    }
    xSpeed = 0;
}

void Entity::move_y() {
    rect.y += ySpeed;
    if (ySpeed > 0) {
        currentMoveDirection = Direction::down;
    }
    else if (ySpeed < 0) {
        currentMoveDirection = Direction::up;
    }
    else {
        currentMoveDirection = Direction::none;
    }
    ySpeed = 0;
}

