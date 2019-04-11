#ifndef LEARNCPP_RENDERWINDOW_H
#define LEARNCPP_RENDERWINDOW_H

#include <string>
#include <SDL.h>

class Rectangle;
class Texture;

class RenderWindow {
public:
    RenderWindow(const std::string& title, int width, int height);
    ~RenderWindow();
    void clear() { SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); SDL_RenderClear(sdlRenderer); }
    void present() { SDL_RenderPresent( sdlRenderer ); }
    void draw(const Texture& texture, const Rectangle& src, const Rectangle& dest);

    void draw(const Rectangle& rect);
private:
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    int width;
    int height;

    friend Texture;
};


#endif //LEARNCPP_RENDERWINDOW_H
