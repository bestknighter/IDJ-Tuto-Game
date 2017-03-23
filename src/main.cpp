#include <cstdio>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
// #include "SDL_net.h"

#include "CMakeVars.hpp"

#include "Game.hpp"

int main(int argc, char** argv) {

    printf("Project Version %d.%d.%d.%d ", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_TWEAK);
    printf(DEBUG?"DEBUG\n":"RELEASE\n");

    Game game ("Gabriel Filipe Botelho Barbosa 12\\0050935", 1024, 600);
    game.Run ();
    
    return 0;
}