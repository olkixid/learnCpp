#include "Texture.h"

#include <iostream>
#include <SDL_image.h>

#include "RenderWindow.h"

namespace fs = boost::filesystem;

Texture::Texture(const fs::path& imagePath, const RenderWindow& contextRenderer) {
    load(imagePath, contextRenderer);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
    texture = 0;
}

void Texture::load(const fs::path& imagePath, const RenderWindow& contextRenderer) {
    //Load image at specified path
    SDL_Surface* gSurface = IMG_Load( imagePath.c_str() );
    if (!gSurface) {
        std::cout << IMG_GetError();
    }

    mw = static_cast<float>(gSurface->w);
    mh = static_cast<float>(gSurface->h);

    //Create texture from surface pixels

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gSurface->w, gSurface->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, gSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //Get rid of old loaded surface
    SDL_FreeSurface( gSurface );
}
