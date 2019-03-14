#ifndef LEARNCPP_TEXTURE_H
#define LEARNCPP_TEXTURE_H

#include <SDL.h>

#include "RenderWindow.h"

class Texture {
public:
    Texture(const char* image_path, RenderWindow& contextRenderer);
    ~Texture();
    void draw_to(RenderWindow& targetRenderer) { SDL_RenderCopy( targetRenderer.get_sdl_renderer(), sdl_texture, NULL, NULL ); }
private:
    SDL_Texture* sdl_texture = nullptr;
};


#endif //LEARNCPP_TEXTURE_H
