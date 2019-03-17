#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Texture.h"
#include "TextureAtlas.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void loop() {
    RenderWindow rwin{"RenderWindow", SCREEN_WIDTH, SCREEN_HEIGHT};
    Texture tex{"../image.png", rwin};
    TextureAtlas atlas{"../res/atlas.json", rwin};

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit ) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        //Clear screen
        rwin.clear();


        //Render texture to screen
        tex.draw_to(rwin, nullptr, nullptr);
        atlas.get_texture().draw_to(rwin, nullptr, nullptr);

        const SDL_Rect& bla = atlas.get_frames().at(std::string{"boxWarning.png"});
        SDL_Rect dest{0, 0, bla.w, bla.h};
        atlas.get_texture().draw_to(rwin, &bla, &dest);

        //Update screen
        rwin.present();
    }
}

int main() {
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    loop();

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    return 0;
}