#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window* gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    SDL_Renderer* gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );


    //Load image at specified path
    SDL_Surface* gSurface = IMG_Load( "../image.png" );
    if (!gSurface) {
        std::cout << IMG_GetError();
    }

    //Create texture from surface pixels
    SDL_Texture* gTexture = SDL_CreateTextureFromSurface( gRenderer, gSurface );
    if (!gTexture) {
        std::cout << IMG_GetError();
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( gSurface );
    gSurface = nullptr;




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
        SDL_RenderClear( gRenderer );

        //Render texture to screen
        SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

        //Update screen
        SDL_RenderPresent( gRenderer );
    }

    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = nullptr;

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