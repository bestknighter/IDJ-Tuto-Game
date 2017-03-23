#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstdio>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

class Game;

#include "State.hpp"

class Game {
  public:
    Game (std::string title, int width, int height);
    ~Game ();
    void Run ();
    SDL_Renderer* GetRenderer ();
    State& GetState ();
    static Game& GetInstance ();
  private:
    static Game* instance;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    State* state;
};

#include "Sprite.hpp"

#endif //_GAME_HPP_