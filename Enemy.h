#ifndef LEARNCPP_ENEMY_H
#define LEARNCPP_ENEMY_H

#include "Entity.h"

class Scene;
class TextureAtlas;

class Enemy : public Entity {
public:
    explicit Enemy(Scene& scene, double x=250, double y=150);

private:
    Enemy(Scene& scene, double x, double y, TextureAtlas& atlas);
    //void hitRight() override;
    //void hitLeft() override;
};


#endif //LEARNCPP_ENEMY_H
