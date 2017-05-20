#include "Resources.hpp"

#include <iterator>

std::unordered_map<std::string, SDL_Texture_shptr> Resources::imageTable {};
std::unordered_map<std::string, Mix_Music_shptr> Resources::musicTable {};
std::unordered_map<std::string, Mix_Chunk_shptr> Resources::soundTable {};
std::unordered_map<std::string, TTF_Font_shptr> Resources::fontTable {};

void Resources::ClearResources() {
    ClearImages();
    ClearMusics();
    ClearSounds();
    ClearFonts();
}

void Resources::DestroyResources() {
    imageTable.clear();
    musicTable.clear();
    soundTable.clear();
    fontTable.clear();
}

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
    // Destroi todas as imagens antes de limpar o vetor
    for ( int i = imageTable.size() - 1; i >= 0; --i ) {
        auto it = imageTable.begin();
        std::advance( it, i );
        if ( it->second.unique() ) {
            imageTable.erase( it );
        }
    }
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

void Resources::ClearMusics() {
    // Destroi todas musicas antes de limpar o vetor
    for ( int i = musicTable.size() - 1; i >= 0; --i ) {
        auto it = musicTable.begin();
        std::advance( it, i );
        if ( it->second.unique() ) {
            musicTable.erase( it );
        }
    }
}

Mix_Chunk_shptr Resources::GetSound( std::string file ) {
    auto it = soundTable.find( file );
    // Se nao achar o som, carregue-a e retorne-a
    if ( it == soundTable.end() ) {
        Mix_Chunk* sound = Mix_LoadWAV( file.c_str() );
        if ( sound == nullptr ) {
            fprintf( stderr,
                     "[ERRO] Nao foi possivel carregar o som no caminho %s (Resources.cpp:Open()): %s\n",
                     file.c_str(),
                     SDL_GetError() );
            return nullptr;
        }
        Mix_Chunk_shptr snd_shptr( sound, [] ( Mix_Chunk* sound ) {
                                                    Mix_FreeChunk( sound );
                                                } );
        soundTable.emplace( file, snd_shptr );
        return snd_shptr;
    } else { // Se achar, so a retorne
        return it->second;
    }
}

void Resources::ClearSounds() {
    // Destroi todos os sons antes de limpar o vetor
    for ( int i = soundTable.size() - 1; i >= 0; --i ) {
        auto it = soundTable.begin();
        std::advance( it, i );
        if ( it->second.unique() ) {
            soundTable.erase( it );
        }
    }
}

TTF_Font_shptr Resources::GetFont( std::string file, int fontSize ) {
    std::string key = file + "-" + std::to_string( fontSize );
    auto it = fontTable.find( key );
    // Se nao achar a fonte, carregue-a e retorne-a
    if ( it == fontTable.end() ) {
        TTF_Font* font = TTF_OpenFont( file.c_str(), fontSize );
        if ( font == nullptr ) {
            fprintf( stderr,
                     "[ERRO] Nao foi possivel carregar a fonte no caminho %s (Resources.cpp:Open()): %s\n",
                     file.c_str(),
                     SDL_GetError() );
            return nullptr;
        }
        TTF_Font_shptr font_shptr( font, [] ( TTF_Font* font ) {
                                                    TTF_CloseFont( font );
                                                } );
        fontTable.emplace( key, font_shptr );
        return font_shptr;
    } else { // Se achar, so a retorne
        return it->second;
    }
}

void Resources::ClearFonts() {
    // Destroi todas as fontes antes de limpar o vetor
    for ( int i = fontTable.size() - 1; i >= 0; --i ) {
        auto it = fontTable.begin();
        std::advance( it, i );
        if ( it->second.unique() ) {
            fontTable.erase( it );
        }
    }
}
