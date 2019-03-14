#include "Texture.h"

#include <iostream>
#include <SDL_image.h>

Texture::Texture(const char* image_path, SDL_Renderer* contextRenderer) {
    //Load image at specified path
    SDL_Surface* gSurface = IMG_Load( image_path );
    if (!gSurface) {
        std::cout << IMG_GetError();
    }

    //Create texture from surface pixels
    sdl_texture = SDL_CreateTextureFromSurface( contextRenderer, gSurface );
    if (!sdl_texture) {
        std::cout << IMG_GetError();
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( gSurface );
}

Texture::~Texture() {
    //Free loaded image
    SDL_DestroyTexture( sdl_texture );
    sdl_texture = nullptr;
}

void Texture::draw_to(SDL_Renderer *targetRenderer) {
    //Render texture to screen
    SDL_RenderCopy( targetRenderer, sdl_texture, NULL, NULL );
}
