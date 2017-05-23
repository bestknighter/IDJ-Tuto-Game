#include <cstdio>

#ifdef _WIN32
    #include "SDL.h"
    #include "SDL_image.h"
    #include "SDL_mixer.h"
    #include "SDL_ttf.h"
    // #include "SDL_net.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
    // #include "SDL2/SDL_net.h"
#elif __unix__
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
    // #include "SDL2/SDL_net.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "Game.hpp"
#include "TitleState.hpp"
#include "Vec2.hpp"

#define TITULO_JOGO "Gabriel Filipe Botelho Barbosa 12\\0050935"
#define JOGO_WIDTH 1024
#define JOGO_HEIGHT 600

int main( int argc __attribute__((unused)), char* argv[] __attribute__((unused)) ) {

    printf( "Project Version %d.%d.%d.%d ", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_TWEAK );
    printf( DEBUG?"DEBUG\n":"RELEASE\n" );

    Game game( TITULO_JOGO, {JOGO_WIDTH, JOGO_HEIGHT} );
    game.Push( new TitleState() );
    game.Run();
    
    return 0;
}
