#ifndef LEARNCPP_TEXTUREATLAS_H
#define LEARNCPP_TEXTUREATLAS_H

#include <string>
#include <map>
#include <boost/filesystem.hpp>

#include "Texture.h"
#include "Rectangle.h"

class RenderWindow;

class TextureAtlas {
public:
    TextureAtlas() = default;
    TextureAtlas(const boost::filesystem::path& atlasPath, const RenderWindow& contextRenderer);
    void load(const boost::filesystem::path& atlasPath, const RenderWindow& contextRenderer);
    const std::map<std::string, Rectangle>& get_frames() const { return frames; };
    const Texture& get_texture() const { return texture; };
private:
    Texture texture;
    std::map<std::string, Rectangle> frames;
};


#endif //LEARNCPP_TEXTUREATLAS_H
