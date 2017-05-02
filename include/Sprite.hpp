#ifndef SPRITE_HPP
#define SPRITE_HPP

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

#include "Vec2.hpp"

class Sprite {
  public:
    Sprite();
    Sprite( std::string file, unsigned int frameCount = 1, float frameTime = 1 );
    ~Sprite();

    // Carrega um imagem para esse sprite
    void Open( std::string file );
    // Seta a regiao de interesse (ROI - Region of Interest) da imagem
    void SetClip( int x, int y, int w, int h );
    // Renderiza a ROI na posicao fornecida
    void Render( int x, int y, float angle = 0 );
    void Update( float dt );
    // Seta manualmente o frame a ser mostrado
    void SetFrame( unsigned int frame );
    void SetFrameCount( unsigned int frameCount );
    void SetFrameTime( float frameTime );
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetScale( Vec2 const& newScale );
    
  private:
    SDL_Texture* texture = nullptr; // A imagem do objeto
    int width = 0;
    int height = 0;
    SDL_Rect clipRect; // ROI da imagem
    Vec2 scale;
    unsigned int frameCount;
    unsigned int currentFrame;
    float elapsedTime;
    float frameTime;
};

#endif // SPRITE_HPP
