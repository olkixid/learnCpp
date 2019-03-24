#include <iostream>
#include <chrono>
#include <thread>

#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Scene.h"

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

    const Uint8 *state = SDL_GetKeyboardState(nullptr);

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

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }


        if (state[SDL_SCANCODE_LEFT]) {
            scene.get_player().run_left();
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            scene.get_player().run_right();
        }
        if (state[SDL_SCANCODE_UP]) {
            scene.get_player().run_up();
        }
        if (state[SDL_SCANCODE_DOWN]) {
            scene.get_player().run_down();
        }

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