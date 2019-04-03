#ifndef LEARNCPP_PLAYER_H
#define LEARNCPP_PLAYER_H

#include <vector>
#include <SDL.h>

#include "Entity.h"

class Scene;
class TextureAtlas;

class Player : public Entity {
public:
    explicit Player(Scene& scene, double x=150, double y=150);
    ~Player();
    void run_left();
    void run_right();
    void run_up();
    void run_down();
    void jump();
private:
    Player(Scene& scene, double x, double y, TextureAtlas& atlas);
};


#endif //LEARNCPP_PLAYER_H
