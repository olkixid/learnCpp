#include "Texture.h"

#include <iostream>
#include <SDL_image.h>

namespace fs = boost::filesystem;

Texture::Texture(const fs::path imagePath, RenderWindow& contextRenderer) {
    load(imagePath, contextRenderer);
}

Texture::~Texture() {
    //Free loaded image
    SDL_DestroyTexture( sdlTexture );
    sdlTexture = nullptr;
}

void Texture::load(const fs::path imagePath, RenderWindow &contextRenderer) {
    //Load image at specified path
    SDL_Surface* gSurface = IMG_Load( imagePath.c_str() );
    if (!gSurface) {
        std::cout << IMG_GetError();
    }

    //Create texture from surface pixels
    sdlTexture = SDL_CreateTextureFromSurface( contextRenderer.get_sdl_renderer(), gSurface );
    if (!sdlTexture) {
        std::cout << IMG_GetError();
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( gSurface );
}
