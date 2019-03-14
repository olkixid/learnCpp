#ifndef LEARNCPP_TEXTURE_H
#define LEARNCPP_TEXTURE_H

#include <SDL.h>

class Texture {
public:
    Texture(const char* image_path, SDL_Renderer* contextRenderer);
    ~Texture();
    void draw_to(SDL_Renderer* targetRenderer);
private:
    SDL_Texture* sdl_texture = nullptr;
};


#endif //LEARNCPP_TEXTURE_H
