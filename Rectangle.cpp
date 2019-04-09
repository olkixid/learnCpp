#include "Rectangle.h"


bool Rectangle::intersects(Rectangle& r2) const {
    if(r2.x >= x + w || x >= r2.x + r2.w || r2.y >= y + h || y >= r2.y + r2.h) {
        return false;
    }
    return true;
}

Rectangle::Rectangle(SDL_Rect *sdlRect)
: x{static_cast<double>(sdlRect->x)},
  y{static_cast<double>(sdlRect->y)},
  w{static_cast<double>(sdlRect->h)},
  h{static_cast<double>(sdlRect->h)} {}