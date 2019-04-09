#include <iostream>
#include <chrono>
#include <thread>

#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Scene.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"

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
    Scene scene{rwin};
    Player player{scene, 150, 450};
    scene.add_entity(player);
    Player player2{scene, 300, 450};
    scene.add_entity(player2);
    Enemy enemy(scene, 450, 450);
    scene.add_entity(enemy);
    Level level{scene, "../res/level1.json", tileSize};
    scene.set_level(&level);


    InputHandler& inputHandler = InputHandler::get_instance();

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

    InputHandler::delete_instance();
    IMG_Quit();
    SDL_Quit();
    return 0;
}