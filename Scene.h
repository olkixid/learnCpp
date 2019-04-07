#ifndef LEARNCPP_SCENE_H
#define LEARNCPP_SCENE_H

#include <map>
#include <vector>
#include <boost/filesystem.hpp>

#include "TextureAtlas.h"

class Level;
class Entity;
class RenderWindow;

class Scene {
public:
    Scene(RenderWindow& debugRenderer);
    void draw_to(RenderWindow& targetRenderer);
    void tick();
    //Player& get_player() { return *pPlayer; }
    void add_entity(Entity& entity) { entities.push_back(&entity); }
    void set_level(Level* pLevel) { this->pLevel = pLevel; }
    TextureAtlas& get_atlas(const boost::filesystem::path& atlasPath);
private:
    Level* pLevel = nullptr;
    std::vector<Entity*> entities;
    // just for debug rects etc:
    RenderWindow& debugRenderWindow;
    std::map<boost::filesystem::path, TextureAtlas> atlases;
};


#endif //LEARNCPP_SCENE_H
