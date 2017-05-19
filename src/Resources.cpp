#include "Resources.hpp"

#include <iterator>

std::unordered_map<std::string, SDL_Texture_shptr> Resources::imageTable {};
std::unordered_map<std::string, Mix_Music_shptr> Resources::musicTable {};

SDL_Texture_shptr Resources::GetImage( std::string file ) {
    auto it = imageTable.find( file );
    // Se nao achar a imagem, carregue-a e retorne-a
    if ( it == imageTable.end() ) {
        SDL_Texture* texture = IMG_LoadTexture( Game::GetInstance().GetRenderer(), file.c_str() );
        if ( texture == nullptr ) {
            fprintf( stderr,
                     "[ERRO] Nao foi possivel carregar a imagem no caminho %s (Resources.cpp:Open()): %s\n",
                     file.c_str(),
                     SDL_GetError() );
            return nullptr;
        }
        SDL_Texture_shptr tex_shptr( texture, [] ( SDL_Texture* texture ) {
                                                    SDL_DestroyTexture( texture );
                                                } );
        imageTable.emplace( file, tex_shptr );
        return tex_shptr;
    } else { // Se achar, so a retorne
        return it->second;
    }
}

void Resources::ClearImages() {
    // Destroi todas as iamgens antes de limpar o vetor
    for ( int i = imageTable.size() - 1; i >= 0; --i ) {
        auto it = imageTable.begin();
        std::advance( it, i );
        if ( it->second.unique() ) {
            imageTable.erase( it );
        }
    }
    imageTable.clear();
}

Mix_Music_shptr Resources::GetMusic( std::string file ) {
    auto it = musicTable.find( file );
    // Se nao achar a musica, carregue-a e retorne-a
    if ( it == musicTable.end() ) {
        Mix_Music* music = Mix_LoadMUS( file.c_str() );
        if ( music == nullptr ) {
            fprintf( stderr,
                     "[ERRO] Nao foi possivel carregar a musica no caminho %s (Resources.cpp:Open()): %s\n",
                     file.c_str(),
                     SDL_GetError() );
            return nullptr;
        }
        Mix_Music_shptr mus_shptr( music, [] ( Mix_Music* music ) {
                                                    Mix_FreeMusic( music );
                                                } );
        musicTable.emplace( file, mus_shptr );
        return mus_shptr;
    } else { // Se achar, so a retorne
        return it->second;
    }
}

void Resources::ClearMusic() {
    // Destroi todas as iamgens antes de limpar o vetor
    for ( int i = musicTable.size() - 1; i >= 0; --i ) {
        auto it = musicTable.begin();
        std::advance( it, i );
        if ( it->second.unique() ) {
            musicTable.erase( it );
        }
    }
    musicTable.clear();
}
