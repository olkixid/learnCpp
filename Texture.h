#ifndef LEARNCPP_TEXTURE_H
#define LEARNCPP_TEXTURE_H

#include <SDL.h>

#include <boost/filesystem.hpp>
#include <utility>

class RenderWindow;

class Texture {
public:
    Texture() = default;
    Texture(Texture&& tex) noexcept : sdlTexture{tex.sdlTexture} {
        tex.sdlTexture = nullptr;
    }
    Texture& operator=(Texture&& tex) {
        std::swap(sdlTexture, tex.sdlTexture);
        return *this;
    }
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(const boost::filesystem::path& imagePath, const RenderWindow& contextRenderer);
    ~Texture();

    void load(const boost::filesystem::path& imagePath, const RenderWindow& contextRenderer);
private:
    SDL_Texture* sdlTexture = nullptr;

    friend RenderWindow;
};


#endif //LEARNCPP_TEXTURE_H
