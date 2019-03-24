#include "Scene.h"

Scene::Scene(RenderWindow& contextRenderer, int tileSize)
    : level{"../res/level1.json", tileSize, contextRenderer},
      player{level.get_texture_atlas()},
      debugRenderWindow{contextRenderer}
{}

void Scene::draw_to(RenderWindow& targetRenderer) {
    level.draw_to(targetRenderer);
    player.draw_to(targetRenderer);
}

void Scene::tick() {
    player.move_x();
    level.check_collision(player, debugRenderWindow);
    player.move_y();
    level.check_collision(player, debugRenderWindow);
}
