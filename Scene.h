#ifndef LEARNCPP_SCENE_H
#define LEARNCPP_SCENE_H

#include <map>
#include <boost/filesystem.hpp>

#include "RenderWindow.h"
#include "Level.h"
#include "Player.h"

class Level;
class Player;

class Scene {
public:
    Scene(RenderWindow& debugRenderer);
    void draw_to(RenderWindow& targetRenderer);
    void tick();
    Player& get_player() { return *pPlayer; }
    void set_player(Player* pPlayer) { this->pPlayer = pPlayer; }
    void set_level(Level* pLevel) { this->pLevel = pLevel; }
    TextureAtlas& get_atlas(const boost::filesystem::path& atlasPath);
private:
    Level* pLevel = nullptr;
    Player* pPlayer = nullptr;
    // just for debug rects etc:
    RenderWindow& debugRenderWindow;
    std::map<boost::filesystem::path, TextureAtlas> atlases;
};


#endif //LEARNCPP_SCENE_H
