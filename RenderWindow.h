#ifndef LEARNCPP_RENDERWINDOW_H
#define LEARNCPP_RENDERWINDOW_H

#include <SDL.h>

class RenderWindow {
public:
    RenderWindow(const char* title, int width, int height);
    ~RenderWindow();
    void clear() { SDL_RenderClear( sdlRenderer ); }
    void present() { SDL_RenderPresent( sdlRenderer ); }
    SDL_Renderer* get_sdl_renderer() { return sdlRenderer; }
private:
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
};


#endif //LEARNCPP_RENDERWINDOW_H
