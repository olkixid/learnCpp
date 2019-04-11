#include "Rectangle.h"

#include <SDL_rect.h>

bool Rectangle::intersects(const Rectangle& r2) const {
    if(r2.mx >= mx + mw || mx >= r2.mx + r2.mw || r2.my >= my + mh || my >= r2.my + r2.mh) {
        return false;
    }
    return true;
}

Rectangle::Rectangle(const SDL_Rect& sdlRect)
: mx{static_cast<double>(sdlRect.x)},
  my{static_cast<double>(sdlRect.y)},
  mw{static_cast<double>(sdlRect.h)},
  mh{static_cast<double>(sdlRect.h)} {}