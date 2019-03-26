#include <iostream>
#include <chrono>
#include <thread>

#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Scene.h"
#include "InputHandler.h"

/*

static unsigned long tikks = 0;

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    std::cout << tikks << std::endl;
    tikks = 0;
    SDL_AddTimer(10000, my_callbackfunc, nullptr);
}

*/


void loop() {
    using namespace std::literals::chrono_literals;
    using clock = std::chrono::high_resolution_clock;
    constexpr auto period = clock::time_point::duration{1s}/60;

    const int tileSize = 70;

    const int screenWidth{ 16*tileSize };
    const int screenHeight{ 10*tileSize };

    RenderWindow rwin{"RenderWindow", screenWidth, screenHeight};
    Scene scene{rwin, tileSize};


    InputHandler inputHandler;
    inputHandler.register_action_callback(SDLK_SPACE, std::bind(&Player::jump, &scene.get_player()), &scene.get_player());
    inputHandler.register_action_callback(SDLK_k, [&inputHandler, &scene]() { inputHandler.unregister_callback(&scene.get_player()); }, nullptr);

    inputHandler.register_state_callback(SDLK_LEFT, std::bind(&Player::run_left, &scene.get_player()), &scene.get_player());
    inputHandler.register_state_callback(SDLK_RIGHT, std::bind(&Player::run_right, &scene.get_player()), &scene.get_player());
    inputHandler.register_state_callback(SDLK_UP, std::bind(&Player::run_up, &scene.get_player()), &scene.get_player());
    inputHandler.register_state_callback(SDLK_DOWN, std::bind(&Player::run_down, &scene.get_player()), &scene.get_player());


    auto nextDrawAfter = clock::now();

    //SDL_AddTimer(10000, my_callbackfunc, nullptr);

    for(bool quit{false}; !quit;) {
        auto now = clock::now();
        if (nextDrawAfter > now) {
            std::this_thread::sleep_for(nextDrawAfter - now);
            nextDrawAfter += period;
        } else {
            nextDrawAfter = now + period;
        }

        quit = inputHandler.handle();

        rwin.clear();

        scene.tick();
        scene.draw_to(rwin);

        rwin.present();

        //tikks++;
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO /* | SDL_INIT_TIMER */);
    IMG_Init(IMG_INIT_PNG);

    loop();

    IMG_Quit();
    SDL_Quit();
    return 0;
}