#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include <memory>

#ifdef _WIN32
    #include "SDL_mixer.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL_mixer.h"
#elif __unix__
    #include "SDL2/SDL_mixer.h"
#else
#   error "Unknown or unsupported compiler"
#endif

class Music {
  public:
    Music();
    Music( std::string file );

    void Play( int times );
    void Stop( int fadeTime = 50);
    void Open( std::string file );
    bool IsOpen();
  private:
    std::shared_ptr<Mix_Music> music;
};

#endif // MUSIC_HPP