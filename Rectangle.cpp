#include "Rectangle.h"

#include <SDL.h>

bool Rectangle::intersects(Rectangle& r2) {
    if(r2.x >= x + w || x >= r2.x + r2.w || r2.y >= y + h || y >= r2.y + r2.h) {
        return false;
    }
    return true;
}

void Rectangle::draw_to(RenderWindow& targetRenderer) {
    SDL_Rect sdlRect{static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h) };
    SDL_RenderDrawRect(targetRenderer.get_sdl_renderer(), &sdlRect);
}
