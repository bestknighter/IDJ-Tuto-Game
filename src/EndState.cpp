#include "EndState.hpp"

#include "Game.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"
#include "Vec2.hpp"

EndState::EndState( StateData stateData )
          : instruction( "./resources/font/Call me maybe.ttf", 50,
                        Text::TextStyle::BLENDED,
                        "ESC para menu, espaco para tentar de novo",
                        {255,255,255,255}, {0.0,0.0} ),
            State() {
    Vec2 textPos( Game::GetInstance().GetScreenSize().x/2, 45 );
    instruction.SetPos( textPos, true, true );
    bg = Sprite( stateData.playerVictory ? "./resources/img/win.jpg" : "./resources/img/lose.jpg" );
    music = Music( stateData.playerVictory ? "./resources/audio/endStateWin.ogg" : "./resources/audio/endStateLose.ogg" );
    music.Play( 0 );
}

void EndState::Update( float dt ) {
    quitRequested = IMinstance.QuitRequested();
    popRequested = IMinstance.KeyPress( ESCAPE_KEY );
    instruction.Update ( dt );
    if ( IMinstance.KeyPress( SPACE_KEY ) ) {
        popRequested = true;
        Game::GetInstance().Push( new StageState() );
    }
}

void EndState::Render() {
    bg.Render( 0,0 );
    instruction.Render( 0,0 );
}

void EndState::Pause() {

}

void EndState::Resume() {

}
