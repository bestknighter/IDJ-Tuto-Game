#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <string>

#ifdef _WIN32
    #include "SDL.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL.h"
#elif __unix__
    #include "SDL.h"
#else
#   error "Unknown or unsupported compiler"
#endif

class State;

#include "Sprite.hpp"

class State {
  public:
    State ();
    bool QuitRequested ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();
  private:
    Sprite bg;
    bool quitRequested = false;
};

#endif // _STATE_HPP_