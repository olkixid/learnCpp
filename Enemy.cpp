#include "Enemy.h"

#include "TextureAtlas.h"
#include "Scene.h"


Enemy::Enemy(Scene& scene, double x, double y) : Enemy{scene, x, y, scene.get_atlas("../res/atlas.json")} {}

Enemy::Enemy(Scene& scene, double x, double y, TextureAtlas& atlas) :
        Entity{atlas.get_texture(), atlas.get_frames().at("blocker_Mad.png")}
{
    rect.x = x;
    rect.y = y;
    rect.w = frame.w;
    rect.h = frame.h;

    xSpeed = 4;
}
