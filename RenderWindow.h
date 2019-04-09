#ifndef LEARNCPP_RENDERWINDOW_H
#define LEARNCPP_RENDERWINDOW_H

#include <string>
#include <SDL.h>

#include "Texture.h"
#include "Rectangle.h"

class RenderWindow {
public:
    RenderWindow(const std::string& title, int width, int height);
    ~RenderWindow();
    void clear() { SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); SDL_RenderClear(sdlRenderer); }
    void present() { SDL_RenderPresent( sdlRenderer ); }
    void draw(const Texture& texture, const SDL_Rect* src, Rectangle& dest) {
        SDL_Rect sdlDest{ static_cast<int>(dest.x), static_cast<int>(dest.y), static_cast<int>(dest.w), static_cast<int>(dest.h) };
        SDL_RenderCopy( sdlRenderer, texture.sdlTexture, src, &sdlDest );
    }
    void draw(const Rectangle& rect);
private:
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    friend Texture;
};


#endif //LEARNCPP_RENDERWINDOW_H
