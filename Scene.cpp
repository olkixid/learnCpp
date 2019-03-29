#include "Scene.h"

Scene::Scene(RenderWindow& debugRenderer) :
      debugRenderWindow{debugRenderer}
{}

void Scene::draw_to(RenderWindow& targetRenderer) {
    pLevel->draw_to(targetRenderer);
    pPlayer->draw_to(targetRenderer);
}

void Scene::tick() {
    pPlayer->move_x();
    pLevel->check_collision(*pPlayer, debugRenderWindow);
    pPlayer->move_y();
    pLevel->check_collision(*pPlayer, debugRenderWindow);
}

TextureAtlas &Scene::get_atlas(const boost::filesystem::path& atlasPath) {
    if (!atlases.count(atlasPath)) {
        return atlases[atlasPath] = TextureAtlas{atlasPath, debugRenderWindow};
    }
    return atlases[atlasPath];
}
