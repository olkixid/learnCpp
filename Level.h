#ifndef LEARNCPP_LEVEL_H
#define LEARNCPP_LEVEL_H

#include <vector>
#include <boost/filesystem.hpp>
#include "boost/multi_array.hpp"

#include <SDL.h>
#include "TextureAtlas.h"

class Level {
public:
    Level(const boost::filesystem::path& levelPath, const RenderWindow& contextRenderer);
    void draw_to(RenderWindow& targetRenderer);
private:
    TextureAtlas atlas;
    //std::vector<std::vector<const SDL_Rect*>> grid;
    boost::multi_array<const SDL_Rect*, 2> grid;
};


#endif //LEARNCPP_LEVEL_H
