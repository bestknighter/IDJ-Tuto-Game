#include "Game.hpp"

Game* Game::instance = nullptr;

Game::Game (std::string title, int width, int height) {
    if (instance == nullptr) {
        instance = this;
    }

    // Inicializando a SDL
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf (stderr, "[ERRO] Falha na inicializacao do SDL (%s:%d): %s\n", __FILE__, __LINE__, SDL_GetError());
    }

    // Inicializando a SDL_image
    int img_inited = IMG_Init (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    if (!(img_inited & IMG_INIT_JPG)) {
        fprintf (stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de JPGs. (%s:%d)\n", __FILE__, __LINE__);
    }
    if (!(img_inited & IMG_INIT_PNG)) {
        fprintf (stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de PNGs. (%s:%d)\n", __FILE__, __LINE__);
    }
    if (!(img_inited & IMG_INIT_TIF)) {
        fprintf (stderr, "[AVISO] SDL_image nao conseguiu inicializar o uso de TIFs. (%s:%d)\n", __FILE__, __LINE__);
    }

    // Criando a janela
    window = SDL_CreateWindow (title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        fprintf (stderr, "[ERRO] Nao foi possivel criar uma janela (%s:%d): %s\n", __FILE__, __LINE__, SDL_GetError());
    }

    // Criando o renderer
    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        fprintf (stderr, "[ERRO] Nao foi possivel criar uma janela (%s:%d): %s\n", __FILE__, __LINE__, SDL_GetError());
    }

    // Inicializando variaveis
    dt = 0;
    frameStart = 0;
    state = new State ();
    srand (time (0));
}

Game::~Game () {
    delete state;
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    IMG_Quit ();
    SDL_Quit ();
}

void Game::Run () {
    state->LoadAssets ();
    int delay;

    // Inicializa o game loop calculando qual e o tempo atual.
    // Permanece nele somente se state nao tiver mandado sair
    // Quando o frame termina, o Delay eh o tempo que faltava para se obter o framerate alvo
    for (frameStart = SDL_GetTicks (); !state->QuitRequested (); SDL_Delay (delay>0 ? delay : 0)) {
        CalculateDeltaTime ();

        // Updates
        InputManager::GetInstance ().Update ();
        state->Update (dt);

        // Renders
        state->Render ();
        SDL_RenderPresent (renderer);

        // Calcula quanto tempo livre esse frame ainda possui
        delay = 1000/frameRate + frameStart - SDL_GetTicks ();
    }
    Resources::ClearImages ();
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

float Game::GetDeltaTime () {
    return dt;
}

void Game::CalculateDeltaTime () {
    int newFrameStart = SDL_GetTicks ();
    dt = (newFrameStart - frameStart)/1000.0;
    #if DEBUG
    // Printa o FPS imediato em que o jogo esta rodando
    // printf ("%f FPS\n", 1.0/dt);
    #endif // DEBUG
    frameStart = SDL_GetTicks ();
}
