#ifndef RESOURCES_HPP
#define RESOURCES_HPP

class Resources;

#include <memory>
#include <string>
#include <unordered_map>

#ifdef _WIN32
    #include "SDL_image.h"
    #include "SDL_mixer.h"
    #include "SDL_ttf.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
#elif __unix__
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "Game.hpp"

#define SDL_Texture_shptr std::shared_ptr<SDL_Texture>
#define Mix_Music_shptr std::shared_ptr<Mix_Music>
#define Mix_Chunk_shptr std::shared_ptr<Mix_Chunk>
#define TTF_Font_shptr std::shared_ptr<TTF_Font>

class Resources {
  public:
    static void ClearResources();
    static void DestroyResources();

    static SDL_Texture_shptr GetImage( std::string file );
    static void ClearImages();
    
    static Mix_Music_shptr GetMusic( std::string file );
    static void ClearMusics();

    static Mix_Chunk_shptr GetSound( std::string file );
    static void ClearSounds();

    static TTF_Font_shptr GetFont( std::string file, int fontSize );
    static void ClearFonts();
  private:
    // Tabelas com os recursos de acordo com seus caminhos
    static std::unordered_map<std::string, SDL_Texture_shptr> imageTable;
    static std::unordered_map<std::string, Mix_Music_shptr> musicTable;
    static std::unordered_map<std::string, Mix_Chunk_shptr> soundTable;
    static std::unordered_map<std::string, TTF_Font_shptr> fontTable;
};

#endif // RESOURCES_HPP
