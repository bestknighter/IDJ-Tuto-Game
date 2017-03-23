#include "Sprite.hpp"

Sprite::Sprite () {
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = 0;
    clipRect.h = 0;
    texture = nullptr;
}

Sprite::Sprite (std::string file) : Sprite () {
    Open (file);
}

Sprite::~Sprite () {
    SDL_DestroyTexture (texture);
}

void Sprite::Open (std::string file) {
    if (texture == nullptr) {
        SDL_DestroyTexture (texture);
    }
    texture = IMG_LoadTexture (Game::GetInstance ().GetRenderer (), file.c_str ());
    if (texture == nullptr) {
        fprintf (stderr, "[ERRO] Nao foi possivel carregar a imagem no caminho %s (Sprite.cpp:Open()): %s\n", file.c_str (), SDL_GetError ());
    } else {
        SDL_QueryTexture (texture, nullptr, nullptr, &width, &height);
        SetClip (0, 0, width, height);
    }
}

void Sprite::SetClip (int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render (int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = clipRect.w;
    dst.h = clipRect.h;
    if (SDL_RenderCopy (Game::GetInstance ().GetRenderer (), texture, &clipRect, &dst) != 0) {
        fprintf (stderr, "[ERRO] Nao foi possivel renderizar a sprite (Sprite.cpp:Render()): %s\n", SDL_GetError ());
    }
}

int Sprite::GetWidth () {
    return clipRect.w;
}

int Sprite::GetHeight () {
    return clipRect.h;
}

bool Sprite::IsOpen () {
    return texture != nullptr;
}