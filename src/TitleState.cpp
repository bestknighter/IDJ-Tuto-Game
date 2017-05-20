#include "TitleState.hpp"

#include "Game.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"
#include "Vec2.hpp"

TitleState::TitleState() : bg( "./resources/img/title.jpg" )
                         , titleText( "./resources/font/Call me maybe.ttf",
                                      50, Text::TextStyle::BLENDED,
                                      "Pressione espaco para comecar",
                                      {255,255,255,255}, Vec2(50,50) ) {
    Vec2 texPos( Game::GetInstance().GetScreenSize().x/2, Game::GetInstance().GetScreenSize().y - 75 );
    titleText.SetPos( texPos, true, true );
}

void TitleState::Update( float dt ) {
    quitRequested = IMinstance.QuitRequested();
    popRequested = IMinstance.KeyPress(ESCAPE_KEY);

    if ( IMinstance.KeyPress( SPACE_KEY ) ) {
        Game::GetInstance().Push( new StageState() );
    }

    titleText.Update( dt );
}

void TitleState::Render() {
    bg.Render( 0, 0 );
    titleText.Render( 0, 0 );
}

void TitleState::Pause() {}

void TitleState::Resume() {}
