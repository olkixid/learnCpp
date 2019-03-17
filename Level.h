#ifndef LEARNCPP_LEVEL_H
#define LEARNCPP_LEVEL_H

#include <vector>
#include <boost/filesystem.hpp>
#include <SDL.h>
#include "TextureAtlas.h"

class Level {
public:
    Level(const boost::filesystem::path& levelPath, const RenderWindow& contextRenderer);
private:
    TextureAtlas atlas;
    std::vector<std::vector<int>> grid;
};


#endif //LEARNCPP_LEVEL_H
