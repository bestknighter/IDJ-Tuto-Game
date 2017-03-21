#include <cstdio>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
// #include "SDL_net.h"

#include "CMakeVars.hpp"

int main(int argc, char** argv) {

    printf("Project Version %d.%d.%d.%d ", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_TWEAK);
    printf(DEBUG?"DEBUG\n":"RELEASE\n");

    /* Inicializa todas as bibliotecas */
    SDL_Init(SDL_INIT_EVERYTHING);
    printf("Initialized SDL\n");

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    printf("Initialized IMG\n");

    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
    printf("Initialized Mix\n");

    TTF_Init();
    printf("Initialized TTF\n");

    // SDLNet_Init();
    // printf("Initialized SDLNet\n");

    /* Fecha todas */
    // SDLNet_Quit();
    // printf("Quited SDLNet\n");

    TTF_Quit();
    printf("Quited TTF\n");

    Mix_Quit();
    printf("Quited Mix\n");

    IMG_Quit();
    printf("Quited IMG\n");

    SDL_Quit();
    printf("Quited SDL\n");
    
    return 0;
}