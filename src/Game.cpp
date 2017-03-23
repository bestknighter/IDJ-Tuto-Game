#include "Game.hpp"

Game* Game::instance = nullptr;

Game::Game (std::string title, int width, int height) {
    if (instance == nullptr) {
        instance = this;
    }

    // Inicializando a SDL
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf (stderr, "[ERRO] Falha na inicializacao do SDL (Game.cpp:Game()): %s\n" , SDL_GetError());
    }

    // Inicializando a SDL_image
    int img_inited = IMG_Init (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    if (!(img_inited & IMG_INIT_JPG)) {
        fprintf (stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de JPGs. (Game.cpp:Game())\n");
    }
    if (!(img_inited & IMG_INIT_PNG)) {
        fprintf (stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de PNGs. (Game.cpp:Game())\n");
    }
    if (!(img_inited & IMG_INIT_TIF)) {
        fprintf (stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de TIFs. (Game.cpp:Game())\n");
    }

    // Criando a janela
    window = SDL_CreateWindow (title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        fprintf (stderr, "[ERRO] Nao foi possivel criar uma janela (Game.cpp:Game()): %s\n", SDL_GetError());
    }

    // Criando o renderer
    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        fprintf (stderr, "[ERRO] Nao foi possivel criar uma janela (Game.cpp:Game()): %s\n", SDL_GetError());
    }
}

Game::~Game () {
    IMG_Quit ();
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_Quit ();
}

/* Game Loop */
void Game::Run () {
    for ( ; !state->QuitRequested (); SDL_Delay (33)) { // 30 FPS? Peasants... -_-
        state->Update (0);
        state->Render ();
        SDL_RenderPresent (renderer);
    }
}

SDL_Renderer* Game::GetRenderer () {
    return renderer;
}

State& Game::GetState () {
    return *state;
}

Game& Game::GetInstance () {
    return *instance;
}