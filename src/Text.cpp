#include "Text.hpp"

#include <cstdio>

#include "Game.hpp"
#include "Resources.hpp"

Text::Text( std::string fontFile, int fontSize,
            TextStyle style, std::string text,
            SDL_Color fgcolor, Vec2 const& pos )
          : text( text ), style( style ),
            fontSize( fontSize ), fgcolor( fgcolor ),
            bgcolor({0,0,0,255}), box( pos, Vec2( 0,0 ) ),
            show( true ) {
    font = Resources::GetFont( fontFile, fontSize );
    texture = nullptr;
    RemakeTexture();
}

Text::~Text() {
    if ( texture != nullptr ) {
        SDL_DestroyTexture( texture.get() );
    }
}

void Text::Update( float dt ) {
    timer.Update( dt );
    if ( 1.0/BLINK_FREQ < timer.Get() ) {
        show = !show;
        timer.Restart();
    }
}

void Text::Render( int cameraX, int cameraY ) {
    if ( !show ) return;
    SDL_Rect src;
    SDL_Rect dst;

    src.x = 0;
    src.y = 0;
    src.w = box.GetTamanho().x;
    src.h = box.GetTamanho().y;

    dst.x = src.x + box.GetPosicao().x - cameraX;
    dst.y = src.y + box.GetPosicao().y - cameraY;
    dst.w = src.w;
    dst.h = src.h;
    if ( SDL_RenderCopy( Game::GetInstance().GetRenderer(), texture.get(), &src, &dst ) != 0 ) {
        fprintf( stderr, "[ERRO] Nao foi possivel renderizar a fonte (%s:%d): %s\n",
                 __FILE__, __LINE__, SDL_GetError() );
    }
}

void Text::SetPos( Vec2 const& pos, bool centerX, bool centerY ) {
    box.SetPosicao( pos - Vec2( centerX*box.GetTamanho().x, centerY*box.GetTamanho().y )/2.0 );
}

void Text::SetText( std::string text ) {
    this->text = text;
    RemakeTexture();
}

void Text::SetForegroundColor( SDL_Color color ) {
    this->fgcolor = color;
    RemakeTexture();
}

void Text::SetStyle( TextStyle style ) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize( int fontSize ) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if ( texture != nullptr ) {
        SDL_DestroyTexture( texture.get() );
    }

    SDL_Surface* surf = nullptr;
    switch ( style ) {
        case TextStyle::SOLID: {
            surf = TTF_RenderText_Solid( font.get(), text.c_str(), fgcolor );
            break;
        }
        case TextStyle::SHADED: {
            surf = TTF_RenderText_Shaded( font.get(), text.c_str(), fgcolor, bgcolor );
            break;
        }
        case TextStyle::BLENDED: {
            surf = TTF_RenderText_Blended( font.get(), text.c_str(), fgcolor );
            break;
        }
    }

    texture.reset( SDL_CreateTextureFromSurface( Game::GetInstance().GetRenderer(), surf ),
                                                 [] (SDL_Texture* texture) {
                                                     SDL_DestroyTexture(texture);
                                                 } );
    SDL_FreeSurface( surf );

    int width;
    int height;
    SDL_QueryTexture( texture.get(), nullptr, nullptr, &width, &height );
    box.SetTamanho( Vec2( width, height ) );
}
