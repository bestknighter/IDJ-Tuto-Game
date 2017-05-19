#include "Music.hpp"

#include "Resources.hpp"

Music::Music() {
    music = nullptr;
}

Music::Music( std::string file ) : Music() {
    Open( file );
}

void Music::Play( int times ) {
    Mix_PlayMusic( music.get(), times );
}

void Music::Stop( int fadeTime ) {
    Mix_FadeOutMusic( fadeTime );
}

void Music::Open( std::string file ) {
    music = Resources::GetMusic( file );
}

bool Music::IsOpen() {
    return music != nullptr;
}
