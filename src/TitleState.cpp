#include "TitleState.hpp"

#include "Game.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"

TitleState::TitleState() : bg( "./Resources/img/title.jpg" ) {}

void TitleState::Update( float dt ) {
    quitRequested = IMinstance.QuitRequested();
    popRequested = IMinstance.KeyPress(ESCAPE_KEY);

    if ( IMinstance.KeyPress( SPACE_KEY ) ) {
        Game::GetInstance().Push( new StageState() );
    }
}

void TitleState::Render() {
    bg.Render( 0, 0 );
}

void TitleState::Pause() {}

void TitleState::Resume() {}
