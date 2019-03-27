#ifndef LEARNCPP_PLAYER_H
#define LEARNCPP_PLAYER_H

#include <vector>
#include <SDL.h>

#include "RenderWindow.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "Rectangle.h"

enum class Direction {
    none,
    up,
    right,
    down,
    left
};

class Player {
public:
    explicit Player(const TextureAtlas& atlas);
    ~Player();
    void draw_to(RenderWindow& targetRenderer);
    void run_left();
    void run_right();
    void run_up();
    void run_down();
    void jump();

    void move_x();
    void move_y();
    const Rectangle& get_rectangle() { return rect; }

    void react_to_overlapping(const Rectangle& otherRect);
private:
    const Texture& texture;
    //std::vector<const SDL_Rect&> animationFrames;
    const SDL_Rect& standingFrame;

    Rectangle rect{150.0, 150.0, 0, 0};
    double xSpeed{0};
    double ySpeed{0};
    Direction currentMoveDirection{Direction::none};
};


#endif //LEARNCPP_PLAYER_H
