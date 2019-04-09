#include "Level.h"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "thirdparty/json.hpp"

#include "Texture.h"
#include "TextureAtlas.h"
#include "Entity.h"
#include "Scene.h"

namespace fs = boost::filesystem;

Level::Level(Scene& scene, const fs::path& levelPath, int tileSize) : tileSize{tileSize} {
    using json = nlohmann::json;

    std::ifstream jsonStream{levelPath.string()};
    json levelJson;
    jsonStream >> levelJson;
    std::string atlasName = levelJson["textureAtlas"];
    std::cout << atlasName << std::endl;
    fs::path atlasPath{ levelPath.parent_path() / atlasName };
    std::cout << atlasPath << std::endl;
    TextureAtlas& atlas = scene.get_atlas(atlasPath);
    pTexture = &atlas.get_texture();

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

void Level::draw_to(RenderWindow& targetRenderer) {
    int x{0};
    int y{0};

    for (const auto& inner : grid) {
        y = 0;
        for (const SDL_Rect* srcRect : inner) {
            if (srcRect) {
                SDL_Rect dest{x, y, tileSize, tileSize};
                targetRenderer.draw(*pTexture, srcRect, &dest);
            }
            y += tileSize;
        }
        x += tileSize;
    }
}

bool Level::check_collision(Entity& entity) {
    const Rectangle& rect = entity.get_rectangle();
    int firstX = static_cast<int>(floor(rect.x/tileSize));
    int lastX = static_cast<int>(floor((rect.x+rect.w)/tileSize));
    int firstY = static_cast<int>(floor(rect.y/tileSize));
    int lastY = static_cast<int>(floor((rect.y+rect.h)/tileSize));

    firstX = std::max<int>(firstX, 0);
    lastX = std::min<int>(lastX, static_cast<int>(grid.shape()[0])-1);
    firstY = std::max<int>(firstY, 0);
    lastY = std::min<int>(lastY, static_cast<int>(grid.shape()[1])-1);

    bool didCollide{false};
    for (int x{firstX}; x<=lastX; x++) {
        for (int y{firstY}; y<=lastY; y++) {
            if (grid[x][y]) {
                Rectangle tileRect{static_cast<double>(x * tileSize), static_cast<double>(y * tileSize),
                                   static_cast<double>(tileSize), static_cast<double>(tileSize)};
                if (rect.intersects(tileRect)) {
                    didCollide = true;
                    entity.react_to_overlapping(tileRect);
                }
            }
        }
    }
    return didCollide;
}


