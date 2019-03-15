#ifndef LEARNCPP_TEXTURE_H
#define LEARNCPP_TEXTURE_H

#include <SDL.h>

#include "RenderWindow.h"

class Texture {
public:
    Texture(const char* imagePath, RenderWindow& contextRenderer);
    ~Texture();
    void draw_to(RenderWindow& targetRenderer) { SDL_RenderCopy( targetRenderer.get_sdl_renderer(), sdlTexture, NULL, NULL ); }
private:
    SDL_Texture* sdlTexture = nullptr;
};


#endif //LEARNCPP_TEXTURE_H
