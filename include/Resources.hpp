#ifndef RESOURCES_HPP
#define RESOURCES_HPP

class Resources;

#include <string>
#include <unordered_map>

#ifdef _WIN32
    #include "SDL_image.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL_image.h"
#elif __unix__
    #include "SDL2/SDL_image.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "Game.hpp"

class Resources {
  public:
    static SDL_Texture* GetImage( std::string file );
    static void ClearImages();
    
  private:
    // Tabela com as imagens de acordo com seus caminhos
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
};

#endif // RESOURCES_HPP
