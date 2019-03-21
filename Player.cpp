#include "Player.h"

Player::Player(const TextureAtlas& atlas) : texture{atlas.get_texture()},
                                            standingFrame{atlas.get_frames().at("p3_front.png")}
{
    const auto& frames = atlas.get_frames();
    rect.w = standingFrame.w;
    rect.h = standingFrame.h;
    /*
    animationFrames.push_back(frames.at("p3_walk01.png");
    animationFrames.push_back(frames.at("p3_walk02.png");
    animationFrames.push_back(frames.at("p3_walk03.png");
    animationFrames.push_back(frames.at("p3_walk04.png");
    animationFrames.push_back(frames.at("p3_walk05.png");
    animationFrames.push_back(frames.at("p3_walk06.png");
    animationFrames.push_back(frames.at("p3_walk07.png");
     */
};

void Player::draw_to(RenderWindow &targetRenderer) {
    SDL_Rect dest{static_cast<int>(rect.x), static_cast<int>(rect.y), standingFrame.w, standingFrame.h};
    texture.draw_to(targetRenderer, &standingFrame, &dest);
    rect.draw_to(targetRenderer);
}


void Player::run_left() {
    rect.x-=5;
}

void Player::run_right() {
    rect.x+=5;
}

void Player::run_up() {
    rect.y-=5;
}

void Player::run_down() {
    rect.y+=5;
}

void Player::jump() {

}
