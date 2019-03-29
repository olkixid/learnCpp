#include "Player.h"

#include "InputHandler.h"

Player::Player(Scene& scene) : texture{scene.get_atlas("../res/atlas.json").get_texture()},
                                            standingFrame{scene.get_atlas("../res/atlas.json").get_frames().at("p3_front.png")}
{
    const auto& frames = scene.get_atlas("../res/atlas.json").get_frames();
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

    InputHandler& inputHandler = InputHandler::get_instance();
    inputHandler.register_action_callback(SDLK_SPACE, std::bind(&Player::jump, this), this);
    inputHandler.register_action_callback(SDLK_k, [&inputHandler, this]() { inputHandler.unregister_callback(this); }, nullptr);

    inputHandler.register_state_callback(SDLK_LEFT, std::bind(&Player::run_left, this), this);
    inputHandler.register_state_callback(SDLK_RIGHT, std::bind(&Player::run_right, this), this);
    inputHandler.register_state_callback(SDLK_UP, std::bind(&Player::run_up, this), this);
    inputHandler.register_state_callback(SDLK_DOWN, std::bind(&Player::run_down, this), this);
};

Player::~Player() {
    InputHandler& inputHandler = InputHandler::get_instance();
    inputHandler.unregister_callback(this);
}

void Player::draw_to(RenderWindow &targetRenderer) {
    SDL_Rect dest{static_cast<int>(rect.x), static_cast<int>(rect.y), standingFrame.w, standingFrame.h};
    texture.draw_to(targetRenderer, &standingFrame, &dest);
    rect.draw_to(targetRenderer);
}


void Player::run_left() {
    xSpeed = -5;
}

void Player::run_right() {
    xSpeed = 5;
}

void Player::run_up() {
    ySpeed = -5;
}

void Player::run_down() {
    ySpeed = 5;
}

void Player::jump() {
    ySpeed = -20;
}

void Player::react_to_overlapping(const Rectangle& otherRect) {
    switch (currentMoveDirection) {
        case Direction::up:
            rect.y = otherRect.y + otherRect.h;
            break;
        case Direction::right:
            rect.x = otherRect.x - rect.w;
            break;
        case Direction::down:
            rect.y = otherRect.y - rect.h;
            break;
        case Direction::left:
            rect.x = otherRect.x + otherRect.w;
            break;
        default:
            break;
    }
}

void Player::move_x() {
    rect.x += xSpeed;
    if (xSpeed > 0) {
        currentMoveDirection = Direction::right;
    }
    else if (xSpeed < 0) {
        currentMoveDirection = Direction::left;
    }
    else {
        currentMoveDirection = Direction::none;
    }
    xSpeed = 0;
}

void Player::move_y() {
    rect.y += ySpeed;
    if (ySpeed > 0) {
        currentMoveDirection = Direction::down;
    }
    else if (ySpeed < 0) {
        currentMoveDirection = Direction::up;
    }
    else {
        currentMoveDirection = Direction::none;
    }
    ySpeed = 0;
}

