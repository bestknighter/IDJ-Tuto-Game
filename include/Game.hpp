#ifndef GAME_HPP
#define GAME_HPP

class Game;

#define FPS_ALVO 120 // 30 FPS is for peasants!!!

#include <string>
#include <stack>
#include <memory>

#ifdef _WIN32
    #include "SDL.h"
    #include "SDL_image.h"
    #include "SDL_mixer.h"
    #include "SDL_ttf.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
#elif __unix__
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "State.hpp"
#include "Vec2.hpp"

class Game {
  public:
    Game( std::string title, Vec2 const& size );
    ~Game();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();

    void Push(State* state);

    void Run(); // Game Loop

    float GetDeltaTime();
    const Vec2 GetScreenSize(); // Retorna o tamanho da tela
    void SetScreenSize( Vec2 const& newSize ); // Modifica o tamanho da tela

  private:
    int frameStart; // Armazena o tick desde a inicializacao da biblioteca SDL ate o inicio do frame
    float dt; // Armazena quanto tempo se passou desde o ultimo frame

    static Game* instance; // Instancia do Game (por ser um singleton)

    State* storedState;
    SDL_Window* window = nullptr; // A janela a ser usada para exibicao
    SDL_Renderer* renderer = nullptr; // O renderer usado pela janela
    std::stack<std::unique_ptr<State>> stateStack;

    const int frameRate = FPS_ALVO; // Limite maximo de fps
    
    void CalculateDeltaTime(); // Calcula quanto tempo se passou desde o ultimo frame
};

#endif // GAME_HPP
