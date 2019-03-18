#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "Level.h"


void loop() {
    const int tileSize = 70;

    const int screenWidth{ 16*tileSize };
    const int screenHeight{ 10*tileSize };

    RenderWindow rwin{"RenderWindow", screenWidth, screenHeight};
    Level level{"../res/level1.json", tileSize, rwin};


    for(bool quit{false}; !quit;) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        rwin.clear();

        level.draw_to(rwin);

        rwin.present();
    }
}

int main() {
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    loop();

    IMG_Quit();
    SDL_Quit();
    return 0;
}