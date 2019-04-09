#ifndef LEARNCPP_RENDERWINDOW_H
#define LEARNCPP_RENDERWINDOW_H

#include <string>
#include <SDL.h>

#include "Texture.h"

class Rectangle;

class RenderWindow {
public:
    RenderWindow(const std::string& title, int width, int height);
    ~RenderWindow();
    void clear() { SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); SDL_RenderClear(sdlRenderer); }
    void present() { SDL_RenderPresent( sdlRenderer ); }
    void draw(const Texture& texture, const SDL_Rect* src, const SDL_Rect* dest) { SDL_RenderCopy( sdlRenderer, texture.sdlTexture, src, dest ); }
    void draw(const Rectangle& rect);
private:
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    friend Texture;
};


#endif //LEARNCPP_RENDERWINDOW_H
