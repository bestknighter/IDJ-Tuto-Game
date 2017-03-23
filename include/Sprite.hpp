#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <cstdio>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

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


#include "Game.hpp"

#endif // _SPRITE_HPP_