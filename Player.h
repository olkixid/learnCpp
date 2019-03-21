#ifndef LEARNCPP_PLAYER_H
#define LEARNCPP_PLAYER_H

#include <vector>
#include <SDL.h>

#include "RenderWindow.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "Rectangle.h"

class Player {
public:
    Player(const TextureAtlas& atlas);
    void draw_to(RenderWindow& targetRenderer);
    void run_left();
    void run_right();
    void run_up();
    void run_down();
    void jump();
private:
    const Texture& texture;
    //std::vector<const SDL_Rect&> animationFrames;
    const SDL_Rect& standingFrame;

    Rectangle rect{150.0, 150.0, 0, 0};
};


#endif //LEARNCPP_PLAYER_H
