#include "StageState.hpp"

#include <string>

#include "Alien.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "EndState.hpp"
#include "InputManager.hpp"
#include "Penguins.hpp"
#include "Resources.hpp"
#include "TitleState.hpp"
#include "Vec2.hpp"

StageState::StageState() : bg ( "./resources/img/ocean.jpg" )
                         , ms ( "./resources/audio/stageState.ogg" ) {
    tileSet = new TileSet( 64, 64, "./resources/img/tileset.png" );
    tileMap = new TileMap( "./resources/map/tileMap.txt", tileSet );
    
    Penguins *p = new Penguins( Vec2( 704, 640 ) );
    objectArray.emplace_back( p );
    Camera::Follow( p );
    objectArray.emplace_back( new Alien( Vec2( 512, 300 ), 3 ) );

    quitRequested = false;
    ms.Play( -1 );
}

StageState::~StageState() {
    delete tileSet;
    delete tileMap;
}

void StageState::LoadAssets() {
    Resources::GetImage( "./resources/img/minionbullet2.png" );
    Resources::GetImage( "./resources/img/penguinbullet.png" );
    Resources::GetImage( "./resources/img/penguindeath.png" );
    Resources::GetImage( "./resources/img/aliendeath.png" );
    Resources::GetImage( "./resources/img/miniondeath.png" );
    Resources::GetSound( "./resources/audio/boom.wav" );
}

void StageState::Update( float dt ) {
    // Sai dessa fase com ESC ou com solicitacoes do OS
    quitRequested = IMinstance.QuitRequested();
    popRequested = IMinstance.KeyPress( ESCAPE_KEY );

    Camera::Update( dt );
    UpdateArray( dt );

    bool animHappening = false;
    // Checa por colisao
    for ( int i = 0; i < objectArray.size()-1; ++i ) {
        if ( objectArray[i]->Is( "Animation" ) ) {
            animHappening = true;
            continue;
        }
        for ( int j = i+1; j < objectArray.size(); ++j ) {
            if ( objectArray[j]->Is( "Animation" ) ) continue;
            if ( Collision::IsColliding( objectArray[i]->box,
                                         objectArray[j]->box,
                                         objectArray[i]->rotation,
                                         objectArray[j]->rotation ) ) {
                // Se houver colisao, notifica ambos
                objectArray[i]->NotifyCollision( *objectArray[j] );
                objectArray[j]->NotifyCollision( *objectArray[i] );
            }
        }
    }

    if ( animHappening ) {
        endDelay.Restart();
    } else if ( 0 == Alien::alienCount || nullptr == Penguins::player ) {
        endDelay.Update( dt );
        ms.Stop(1.5*END_DELAY*1000);
    }

    if ( END_DELAY < endDelay.Get() ) {
        GameOver( 0 == Alien::alienCount );
    }

}

void StageState::Render() {
    bg.Render( 0, 0 );
    tileMap->Render( Camera::pos.x, Camera::pos.y, 0, 0 ); // Renderiza camada base do mapa
    RenderArray();
    tileMap->Render( Camera::pos.x, Camera::pos.y, 1 ); // Por ultimo renderiza o resto do mapa
}

void StageState::Pause() {
    ms.Stop();
}

void StageState::Resume() {
    ms.Play( -1 );
}

void StageState::GameOver( bool playerWon ) {
    popRequested = true;
    Game::GetInstance().Push( new EndState( {playerWon} ) );
}
