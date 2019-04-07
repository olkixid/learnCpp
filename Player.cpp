#include "Player.h"

#include "Scene.h"
#include "Texture.h"
#include "InputHandler.h"


Player::Player(Scene& scene, double x, double y) : Player{scene, x, y, scene.get_atlas("../res/atlas.json")} {}

Player::Player(Scene& scene, double x, double y, TextureAtlas& atlas) :
Entity{atlas.get_texture(), atlas.get_frames().at("p3_front.png")}
{
    rect.x = x;
    rect.y = y;
    rect.w = frame.w;
    rect.h = frame.h;


    InputHandler& inputHandler = InputHandler::get_instance();
    inputHandler.register_action_callback(SDLK_SPACE, std::bind(&Player::jump, this), this);
    inputHandler.register_action_callback(SDLK_k, [&inputHandler, this]() { inputHandler.unregister_callback(this); }, nullptr);

    inputHandler.register_state_callback(SDLK_LEFT, std::bind(&Player::run_left, this), this);
    inputHandler.register_state_callback(SDLK_RIGHT, std::bind(&Player::run_right, this), this);
    inputHandler.register_state_callback(SDLK_UP, std::bind(&Player::run_up, this), this);
    inputHandler.register_state_callback(SDLK_DOWN, std::bind(&Player::run_down, this), this);
}

Player::~Player() {
    InputHandler& inputHandler = InputHandler::get_instance();
    inputHandler.unregister_callback(this);
}


void Player::run_left() {
    xSpeed -= 5;
}

void Player::run_right() {
    xSpeed += 5;
}

void Player::run_up() {
    ySpeed -= 5;
}

void Player::run_down() {
    ySpeed += 5;
}

void Player::jump() {
    ySpeed -= 20;
}

void Player::did_move() {
    xSpeed = 0;
    ySpeed = 0;
}
