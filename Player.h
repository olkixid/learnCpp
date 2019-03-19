#ifndef LEARNCPP_PLAYER_H
#define LEARNCPP_PLAYER_H

#include <vector>
#include <SDL.h>

#include "RenderWindow.h"
#include "Texture.h"
#include "TextureAtlas.h"

class Player {
public:
    Player(const TextureAtlas& atlas);
    void draw_to(RenderWindow& targetRenderer);
    void runLeft();
    void runRight();
    void jump();
private:
    const Texture& texture;
    //std::vector<const SDL_Rect&> animationFrames;
    const SDL_Rect& standingFrame;

    double xPos{150.0};
    double yPos{150.0};
};


#endif //LEARNCPP_PLAYER_H
