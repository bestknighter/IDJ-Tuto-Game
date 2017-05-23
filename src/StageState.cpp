#include "StageState.hpp"

#include <cstdlib>
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
    
    Vec2 playerInitialPos( 704, 640 );
    Penguins *p = new Penguins( playerInitialPos );
    objectArray.emplace_back( p );
    Camera::Follow( p );

    float distanciaMedia = 500;
    for ( int i = 2+(int)(4*rand()/(RAND_MAX+1)); i > 0; --i ) { // Random int in [2,5]
        float angle = 2*M_PI*rand()/(RAND_MAX+1); // Random float in [0,2*pi)
        float distance = distanciaMedia - 100 + 200*rand()/RAND_MAX; // Random float in [distanciaMedia-100,distanciaMedia+100]
        Vec2 alienPos = Vec2::FromPolar( distance, angle );

        int nMinions = 1+(int)(7*rand()/(RAND_MAX+1)); // Random int in [1,7]
        objectArray.emplace_back( new Alien( alienPos + playerInitialPos, nMinions ) );
    }

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
    for ( int i = 0; i < (int)objectArray.size()-1; ++i ) {
        if ( objectArray[i]->Is( "Animation" ) ) {
            animHappening = true;
            continue;
        }
        for ( int j = i+1; j < (int)objectArray.size(); ++j ) {
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
        ms.Stop(1.25*END_DELAY*1000);
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
