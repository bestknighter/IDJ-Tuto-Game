#include "Game.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "InputManager.hpp"
#include "Resources.hpp"

Game* Game::instance = nullptr;

Game::Game( std::string title, Vec2 const& size ) {
    if ( instance == nullptr ) {
        instance = this;
    }

    // Inicializando a SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) ) {
        fprintf( stderr, "[ERRO] Falha na inicializacao do SDL (%s:%d): %s\n",
                  __FILE__, __LINE__, SDL_GetError() );
    }

    // Inicializando a SDL_image
    int img_inited = IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF );
    if ( !(img_inited & IMG_INIT_JPG) ) {
        fprintf( stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de JPGs. (%s:%d)\n",
                  __FILE__, __LINE__ );
    }
    if ( !(img_inited & IMG_INIT_PNG) ) {
        fprintf( stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de PNGs. (%s:%d)\n",
                 __FILE__, __LINE__ );
    }
    if ( !(img_inited & IMG_INIT_TIF) ) {
        fprintf( stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de TIFs. (%s:%d)\n",
                 __FILE__, __LINE__ );
    }

    // Criando a janela
    window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, size.x, size.y, 0 );
    if ( window == nullptr ) {
        fprintf( stderr, "[ERRO] Nao foi possivel criar uma janela (%s:%d): %s\n",
                 __FILE__, __LINE__, SDL_GetError() );
    }

    // Criando o renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if ( renderer == nullptr ) {
        fprintf( stderr, "[ERRO] Nao foi possivel criar uma janela (%s:%d): %s\n",
                 __FILE__, __LINE__, SDL_GetError() );
    }

    // Inicializando variaveis
    dt = 0;
    frameStart = 0;
    storedState = nullptr;
    srand( time( 0 ) );
}

Game::~Game() {
    if ( storedState != nullptr ) {
        delete storedState;
    }
    while ( !stateStack.empty() ) {
        stateStack.pop();
    }
    Resources::ClearImages();
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();
}

void Game::Run() {
    State* state;
    if ( storedState != nullptr ) {
        stateStack.emplace( storedState );
        storedState = nullptr;
        state = stateStack.top().get();
    } else {
        fprintf( stderr, "[ERRO] Jogo sem estado inicial\n");
        return;
    }

    state->LoadAssets();

    // Inicializa o game loop calculando qual e o tempo atual.
    // Permanece nele somente se state nao tiver mandado sair
    // Quando o frame termina, o Delay eh o tempo que faltava para se obter o framerate alvo
    int delay;
    state->Resume();
    for ( frameStart = SDL_GetTicks(); !( state->QuitRequested() || stateStack.empty() ); SDL_Delay(delay > 0 ? delay : 0) ) {
        CalculateDeltaTime();

        // Updates
        IMinstance.Update();
        state->Update( dt );

        // Renders
        state->Render();
        SDL_RenderPresent( renderer );

        // Pilha
        if ( state->PopRequested() ) {
            stateStack.pop();
            if ( !stateStack.empty() ) {
                state = stateStack.top().get();
                state->Resume();
            }
            Resources::ClearImages();
        }
        if ( storedState != nullptr ) {
            state->Pause();
            stateStack.emplace( storedState );
            storedState = nullptr;
            state = stateStack.top().get();
            state->LoadAssets();
            state->Resume();
        }

        // Calcula quanto tempo livre esse frame ainda possui
        delay = 1000/frameRate + frameStart - SDL_GetTicks();
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Push(State* state) {
    storedState = state;
    // stateStack.emplace_back(state);
}

State& Game::GetCurrentState() {
    return *stateStack.top();
}

Game& Game::GetInstance() {
    return *instance;
}

float Game::GetDeltaTime() {
    return dt;
}

void Game::CalculateDeltaTime() {
    dt = (SDL_GetTicks() - frameStart)/1000.0;
    #if DEBUG
    // Printa o FPS imediato em que o jogo esta rodando
    // printf( "%f FPS\n", 1.0/dt );
    #endif // DEBUG
    frameStart = SDL_GetTicks();
}

const Vec2 Game::GetScreenSize() {
    if ( nullptr == window ) {
        return Vec2( 0, 0 );
    }
    int w = 0;
    int h = 0;
    SDL_GetWindowSize( window, &w, &h );
    return Vec2( w, h );
}

void Game::SetScreenSize( Vec2 const& newSize ) {
    SDL_SetWindowSize( window, (int)newSize.x, (int)newSize.y );
}
