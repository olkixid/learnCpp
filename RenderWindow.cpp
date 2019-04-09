#include "RenderWindow.h"

#include "Rectangle.h"

RenderWindow::RenderWindow(const std::string& title, int width, int height) {
    sdlWindow = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
    sdlRenderer = SDL_CreateRenderer( sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

RenderWindow::~RenderWindow() {
    //Destroy window
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

void RenderWindow::draw(const Rectangle &rect) {
    SDL_Rect sdlRect{static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.w), static_cast<int>(rect.h) };
    SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(sdlRenderer, &sdlRect);
}
