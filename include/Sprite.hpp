#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

class Sprite;

#include <string>

#ifdef _WIN32
    #include "SDL.h"
    #include "SDL_image.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
#elif __unix__
    #include "SDL.h"
    #include "SDL_image.h"
#else
#   error "Unknown or unsupported compiler"
#endif

class Sprite {
  public:
    Sprite ();
    Sprite (std::string file);
    ~Sprite ();
    void Open (std::string file);
    void SetClip (int x, int y, int w, int h);
    void Render (int x, int y);
    int GetWidth ();
    int GetHeight ();
    bool IsOpen ();
  private:
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;
    SDL_Rect clipRect;
};

#include <cstdio>

#include "Game.hpp"
#include "Resources.hpp"

#endif // _SPRITE_HPP_