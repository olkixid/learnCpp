#include "TextureAtlas.h"

#include <fstream>
#include <iostream>

#include "thirdparty/json.hpp"

namespace fs = boost::filesystem;

TextureAtlas::TextureAtlas(const fs::path& atlasPath, const RenderWindow& contextRenderer) {
   load(atlasPath, contextRenderer);
}

void TextureAtlas::load(const boost::filesystem::path &atlasPath, const RenderWindow &contextRenderer) {
    using json = nlohmann::json;

    std::ifstream jsonStream{atlasPath.string()};
    json atlasJson;
    jsonStream >> atlasJson;
    std::string imageName = atlasJson["meta"]["image"];
    std::cout << imageName << std::endl;
    fs::path imagePath{ atlasPath.parent_path() / imageName };
    std::cout << imagePath << std::endl;
    texture.load(imagePath, contextRenderer);
    const auto& jsonFrames = atlasJson["frames"];
    for (const auto& item : jsonFrames.items()) {
        const std::string& key = item.key();
        json frame = item.value()["frame"];
        double x = frame["x"];
        double y = frame["y"];
        double w = frame["w"];
        double h = frame["h"];
        frames[key] = Rectangle{x, y, w, h};
    }

    for (const auto& el : frames) {
        std::cout << el.first << ", x:" << el.second.x() << ", y:" << el.second.y() << ", w:" << el.second.w() << ", h:" << el.second.h() << std::endl;
    }

}
