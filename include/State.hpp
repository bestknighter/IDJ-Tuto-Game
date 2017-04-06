#ifndef _STATE_HPP_
#define _STATE_HPP_

class State;

#include <vector>
#include <memory>

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

#include "Sprite.hpp"
#include "GameObject.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"

class State {
  public:
    State ();
    ~State ();
    bool QuitRequested ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();
  private:
    void Input ();
    void AddObject (float mouseX, float mouseY);
    Sprite bg;
    bool quitRequested = false;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#include <string>

#include "Vec2.hpp"
#include "Face.hpp"

#endif // _STATE_HPP_