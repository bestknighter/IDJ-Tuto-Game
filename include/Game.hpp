#ifndef _GAME_HPP_
#define _GAME_HPP_

class Game;

#include <string>

#ifdef _WIN32
    #include "SDL.h"
    #include "SDL_image.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
#elif __unix__
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "State.hpp"

#define FPS_ALVO 120 // 30 FPS is for peasants!!!

class Game {
  public:
    Game (std::string title, int width, int height);
    ~Game ();
    void Run (); // Game Loop
    SDL_Renderer* GetRenderer ();
    State& GetState ();
    static Game& GetInstance ();
    float GetDeltaTime ();
  private:
    static Game* instance; // Instancia do Game (por ser um singleton)
    SDL_Window* window = nullptr; // A janela a ser usada para exibicao
    SDL_Renderer* renderer = nullptr; // O renderer usado pela janela
    State* state; // Fase inicial do jogo
    int frameStart; // Armazena o tick desde a inicializacao da biblioteca SDL ate o inicio do frame
    const int frameRate = FPS_ALVO; // Limite maximo de fps
    float dt; // Armazena quanto tempo se passou desde o ultimo frame
    void CalculateDeltaTime (); // Calcula quanto tempo se passou desde o ultimo frame
};

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Resources.hpp"
#include "InputManager.hpp"

#endif //_GAME_HPP_
