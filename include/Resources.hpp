#ifndef RESOURCES_HPP
#define RESOURCES_HPP

class Resources;

#include <memory>
#include <string>
#include <unordered_map>

#ifdef _WIN32
    #include "SDL_image.h"
    #include "SDL_mixer.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
#elif __unix__
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "Game.hpp"

#define SDL_Texture_shptr std::shared_ptr<SDL_Texture>
#define Mix_Music_shptr std::shared_ptr<Mix_Music>
#define Mix_Chunk_shptr std::shared_ptr<Mix_Chunk>

class Resources {
  public:
    static void ClearResources();

    static SDL_Texture_shptr GetImage( std::string file );
    static void ClearImages();
    
    static Mix_Music_shptr GetMusic( std::string file );
    static void ClearMusics();

    static Mix_Chunk_shptr GetSound( std::string file );
    static void ClearSounds();
  private:
    // Tabelas com os recursos de acordo com seus caminhos
    static std::unordered_map<std::string, SDL_Texture_shptr> imageTable;
    static std::unordered_map<std::string, Mix_Music_shptr> musicTable;
    static std::unordered_map<std::string, Mix_Chunk_shptr> soundTable;
};

#endif // RESOURCES_HPP
