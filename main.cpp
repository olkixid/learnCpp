#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void loop(SDL_Renderer* renderer) {

    Texture tex{"../image.png", renderer};

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
        SDL_RenderClear( renderer );

        //Render texture to screen
        tex.draw_to(renderer);

        //Update screen
        SDL_RenderPresent( renderer );
    }
}

int main() {
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window* gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    SDL_Renderer* gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

    loop(gRenderer);

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gRenderer = nullptr;
    gWindow = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    return 0;
}