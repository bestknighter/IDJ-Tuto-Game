#include "Resources.hpp"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable{};

SDL_Texture* Resources::GetImage (std::string file) {
    auto it = imageTable.find (file);
    if (it == imageTable.end()) {
        SDL_Texture* texture = IMG_LoadTexture (Game::GetInstance ().GetRenderer (), file.c_str ());
        if (texture == nullptr) {
            fprintf (stderr, "[ERRO] Nao foi possivel carregar a imagem no caminho %s (Resources.cpp:Open()): %s\n", file.c_str (), SDL_GetError ());
        }
        imageTable.emplace(file, texture);
        return texture;
    } else {
        return it->second;
    }
}

void Resources::ClearImages () {
    for (auto it = imageTable.begin (); it != imageTable.end (); ++it) {
        SDL_DestroyTexture (it->second);
    }
    imageTable.clear();
}