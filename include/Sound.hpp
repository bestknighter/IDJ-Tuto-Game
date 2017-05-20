#ifndef SOUND_HPP
#define SOUND_HPP

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

class Sound {
  public:
    Sound();
    Sound( std::string file );

    void Play( int times = 0 );
    void Stop();
    void Open( std::string file );
    bool IsOpen();
  private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel;    
};

#endif // SOUND_HPP
