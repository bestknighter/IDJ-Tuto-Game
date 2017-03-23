#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <string>

#include "SDL.h"

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