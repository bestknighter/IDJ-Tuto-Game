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
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
#else
#   error "Unknown or unsupported compiler"
#endif

class Sprite {
  public:
    Sprite ();
    Sprite (std::string file);
    ~Sprite ();
    void Open (std::string file); // Carrega um imagem para esse sprite
    void SetClip (int x, int y, int w, int h); // Seta a regiao de interesse (ROI - Region of Interest) da imagem
    void Render (int x, int y); // Renderiza a ROI na posicao fornecida
    int GetWidth ();
    int GetHeight ();
    bool IsOpen ();
  private:
    SDL_Texture* texture = nullptr; // A imagem do objeto
    int width = 0;
    int height = 0;
    SDL_Rect clipRect; // ROI da imagem
};

#include <cstdio>

#include "Game.hpp"
#include "Resources.hpp"

#endif // _SPRITE_HPP_
