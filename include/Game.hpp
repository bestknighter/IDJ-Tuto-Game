#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstdio>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

class Game {
  public:
    Game (std::string, int, int);
    ~Game ();
    void Run ();
    SDL_Renderer* GetRenderer ();
    // State& GetState ();
    static Game& GetInstance ();
  private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    // State* state;
};

#endif //_GAME_HPP_