#include "RenderWindow.h"

#include "Rectangle.h"
#include "Texture.h"

RenderWindow::RenderWindow(const std::string& title, int width, int height)
: width{width},
  height{height}
{
    sdlWindow = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
    sdlRenderer = SDL_CreateRenderer( sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

RenderWindow::~RenderWindow() {
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}


//perhaps round instead of casting??
void RenderWindow::draw(const Rectangle &rect) {
    double flippedY = height - rect.y() - rect.h();
    SDL_Rect sdlRect{static_cast<int>(rect.x()), static_cast<int>(flippedY), static_cast<int>(rect.w()), static_cast<int>(rect.h()) };


    SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(sdlRenderer, &sdlRect);
}

void RenderWindow::draw(const Texture &texture, const SDL_Rect *src, Rectangle &dest) {
    double flippedY = height - dest.y() - dest.h();
    SDL_Rect sdlDest{ static_cast<int>(dest.x()), static_cast<int>(flippedY), static_cast<int>(dest.w()), static_cast<int>(dest.h()) };
    SDL_RenderCopy( sdlRenderer, texture.sdlTexture, src, &sdlDest );
}
