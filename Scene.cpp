#include "Scene.h"

#include "TextureAtlas.h"
#include "Entity.h"
#include "Level.h"

Scene::Scene(RenderWindow& debugRenderer) :
      debugRenderWindow{debugRenderer}
{}

void Scene::draw_to(RenderWindow& targetRenderer) {
    pLevel->draw_to(targetRenderer);
    for (Entity* pEntity : entities) {
        pEntity->draw_to(targetRenderer);
    }
}

void Scene::tick() {
    for (Entity* pEntity : entities) {
        pEntity->move(*pLevel);
    }
}

TextureAtlas &Scene::get_atlas(const boost::filesystem::path& atlasPath) {
    if (!atlases.count(atlasPath)) {
        return atlases[atlasPath] = TextureAtlas{atlasPath, debugRenderWindow};
    }
    return atlases[atlasPath];
}
