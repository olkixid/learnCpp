#include "Player.h"

Player::Player(const TextureAtlas& atlas) : texture{atlas.get_texture()},
                                            standingFrame{atlas.get_frames().at("p3_front.png")}
{
    const auto& frames = atlas.get_frames();
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
    SDL_Rect dest{static_cast<int>(xPos), static_cast<int>(yPos), standingFrame.w, standingFrame.h};
    texture.draw_to(targetRenderer, &standingFrame, &dest);
}


void Player::run_left() {
    xPos-=5;
}

void Player::run_right() {
    xPos+=5;
}

void Player::run_up() {
    yPos-=5;
}

void Player::run_down() {
    yPos+=5;
}

void Player::jump() {

}
