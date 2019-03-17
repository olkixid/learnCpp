#ifndef LEARNCPP_TEXTURE_H
#define LEARNCPP_TEXTURE_H

#include <SDL.h>

#include "RenderWindow.h"

#include <boost/filesystem.hpp>

class Texture {
public:
    Texture() = default;
    Texture(const boost::filesystem::path& imagePath, const RenderWindow& contextRenderer);
    ~Texture();

    void load(const boost::filesystem::path& imagePath, const RenderWindow& contextRenderer);
    void draw_to(RenderWindow& targetRenderer, const SDL_Rect* src, const SDL_Rect* dest) const { SDL_RenderCopy( targetRenderer.get_sdl_renderer(), sdlTexture, src, dest ); }
private:
    SDL_Texture* sdlTexture = nullptr;
};


#endif //LEARNCPP_TEXTURE_H
