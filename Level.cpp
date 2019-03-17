#include "Level.h"

#include <iostream>

#include "thirdparty/json.hpp"

#include "Texture.h"

namespace fs = boost::filesystem;

Level::Level(const fs::path& levelPath, const RenderWindow& contextRenderer) {
    using json = nlohmann::json;

    std::ifstream jsonStream{levelPath.string()};
    json levelJson;
    jsonStream >> levelJson;
    std::string atlasName = levelJson["textureAtlas"];
    std::cout << atlasName << std::endl;
    fs::path atlasPath{ levelPath.parent_path() / atlasName };
    std::cout << atlasPath << std::endl;
    atlas.load(atlasPath, contextRenderer);

    std::map<int, const SDL_Rect*> tileEnum;
    const auto& tileEnumJson = levelJson["tileEnum"];
    for (const auto& item : tileEnumJson.items()) {
        int num = item.value();
        const std::string& name = item.key();

        const auto& frames = atlas.get_frames();
        const SDL_Rect* pRect = nullptr;
        try {
            pRect = &frames.at(name);
        } catch (...) {}

        tileEnum[num] = pRect;
    }


    const auto& gridJson = levelJson["grid"];
    unsigned xSize{0};
    unsigned ySize{0};
    for (const auto& row : gridJson) {
        unsigned currentRowSize = row.size();
        xSize = currentRowSize > xSize ? currentRowSize : xSize;
        ++ySize;
    }

    decltype(grid)::extent_gen extents;
    grid.resize(extents[xSize][ySize]);


    for (unsigned y{0}; y<gridJson.size(); ++y) {
        const auto& inner = gridJson[y];
        for (unsigned x{0}; x<inner.size(); ++x) {
            try{
                int num = inner.at(x);
                grid[x][y] = tileEnum.at(num);
            } catch (...) {
                grid[x][y] = nullptr;
            }
        }
    }

}

void Level::draw_to(RenderWindow &targetRenderer) {
    const int tileSize{35};
    int x{0};
    int y{0};

    const Texture& tex = atlas.get_texture();
    for (const auto& inner : grid) {
        y = 0;
        for (const SDL_Rect* srcRect : inner) {
            if (srcRect) {
                SDL_Rect dest{x, y, tileSize, tileSize};
                tex.draw_to(targetRenderer, srcRect, &dest);
            }
            y += tileSize;
        }
        x += tileSize;
    }
}
