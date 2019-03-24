#ifndef LEARNCPP_SCENE_H
#define LEARNCPP_SCENE_H

#include "RenderWindow.h"
#include "Level.h"
#include "Player.h"

class Scene {
public:
    Scene(RenderWindow& contextRenderer, int tileSize);
    void draw_to(RenderWindow& targetRenderer);
    void tick();
    Player& get_player() { return player; }
private:
    Level level;
    Player player;
    // just for debug rects etc:
    RenderWindow& debugRenderWindow;
};


#endif //LEARNCPP_SCENE_H
