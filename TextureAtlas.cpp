#include "TextureAtlas.h"

#include <fstream>
#include <string>
#include <iostream>

#include "thirdparty/json.hpp"

namespace fs = boost::filesystem;

TextureAtlas::TextureAtlas(const fs::path atlasPath, RenderWindow &contextRenderer) {
    using json = nlohmann::json;

    std::ifstream jsonStream{atlasPath.string()};
    json atlasJson;
    jsonStream >> atlasJson;
    std::string imageName = atlasJson["meta"]["image"];
    std::cout << imageName << std::endl;
    fs::path imagePath{ atlasPath.parent_path() / imageName };
    std::cout << imagePath << std::endl;
    texture.load(imagePath.c_str(), contextRenderer);
    auto jsonFrames = atlasJson["frames"];
    for (auto item : jsonFrames.items()) {
        std::string key = item.key();
        json frame = item.value()["frame"];
        int x = frame["x"];
        int y = frame["y"];
        int w = frame["w"];
        int h = frame["h"];
        frames[key] = SDL_Rect{x, y, w, h};
    }
/*
    for (auto el : frames) {
        std::cout << el.first << ", x:" << el.second.x << ", y:" << el.second.y << ", w:" << el.second.w << ", h:" << el.second.h << std:: endl;
    }
*/
}
