#ifndef TEXT_HPP
#define TEXT_HPP

#define BLINK_FREQ 1.5

#include <string>
#include <memory>

#ifdef _WIN32
    #include "SDL_ttf.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL_ttf.h"
#elif __unix__
    #include "SDL2/SDL_ttf.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "Rect.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"

class Text {
  public:
    enum TextStyle {
        SOLID,
        SHADED,
        BLENDED
    };

    Text( std::string fontFile, int fontSize,
          TextStyle style, std::string text,
          SDL_Color color, Vec2 const& pos );
    ~Text();

    void Update( float dt );
    void Render( int cameraX = 0, int cameraY = 0 );

    void SetPos( Vec2 const& pos,
                 bool centerX = false,
                 bool centerY = false );
    
    void SetText( std::string text );
    void SetForegroundColor( SDL_Color color );
    void SetStyle( TextStyle style );
    void SetFontSize( int fontSize );
  private:
    std::shared_ptr<TTF_Font> font;
    std::shared_ptr<SDL_Texture> texture;

    std::string text;
    TextStyle style;
    int fontSize;
    SDL_Color fgcolor;
    SDL_Color bgcolor;
    Rect box;

    bool show;
    Timer timer;

    void RemakeTexture();
};

#endif // TEXT_HPP
