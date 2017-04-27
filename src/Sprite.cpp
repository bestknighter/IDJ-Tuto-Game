#include "Sprite.hpp"

#include <cstdio>

#include "Game.hpp"
#include "Resources.hpp"

Sprite::Sprite () {
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = 0;
    clipRect.h = 0;
    texture = nullptr;
    width = 0;
    height = 0;
    scale = Vec2 (1,1);
}

Sprite::Sprite (std::string file) : Sprite () {
    Open (file);
}

Sprite::~Sprite () {
    
}

void Sprite::Open (std::string file) {
    texture = Resources::GetImage (file);
    SDL_QueryTexture (texture, nullptr, nullptr, &width, &height);
    SetClip (0, 0, width, height);
}

void Sprite::SetClip (int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render (int x, int y, float angle) {
    SDL_Rect dst; // Onde na tela a ROI vai aparecer
    dst.x = x;
    dst.y = y;
    dst.w = clipRect.w*scale.x;
    dst.h = clipRect.h*scale.y;
    if (SDL_RenderCopyEx (Game::GetInstance ().GetRenderer (), texture, &clipRect, &dst, 360*angle/(2*M_PI), nullptr, SDL_FLIP_NONE) != 0) {
        fprintf (stderr, "[ERRO] Nao foi possivel renderizar a sprite (%s:%d): %s\n", __FILE__, __LINE__, SDL_GetError ());
    }
}

int Sprite::GetWidth () {
    return clipRect.w*scale.x;
}

int Sprite::GetHeight () {
    return clipRect.h*scale.y;
}

bool Sprite::IsOpen () {
    return texture != nullptr;
}

void Sprite::SetScale (Vec2 const& newScale) {
    scale = newScale;
}
