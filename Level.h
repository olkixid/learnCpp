#ifndef LEARNCPP_LEVEL_H
#define LEARNCPP_LEVEL_H

#include <vector>
#include <boost/filesystem.hpp>
#include <boost/multi_array.hpp>

#include <SDL.h>
#include "TextureAtlas.h"
#include "Rectangle.h"

class Level {
public:
    Level(const boost::filesystem::path& levelPath, int tileSize, const RenderWindow& contextRenderer);
    void draw_to(RenderWindow& targetRenderer);
    const TextureAtlas& get_texture_atlas() { return atlas; }

    bool check_collision(const Rectangle& rect, RenderWindow& targetRenderer);
private:
    TextureAtlas atlas;
    //std::vector<std::vector<const SDL_Rect*>> grid;
    boost::multi_array<const SDL_Rect*, 2> grid;
    int tileSize;
};


#endif //LEARNCPP_LEVEL_H
