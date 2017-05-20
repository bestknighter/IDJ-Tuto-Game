#include "Penguins.hpp"

#include <iostream>

#include "Animation.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"

Penguins* Penguins::player = nullptr;

Penguins::Penguins( Vec2 const& pos ) : GameObject()
                                      , bodySp( "./resources/img/penguin.png" )
                                      , cannonSp( "./resources/img/cubngun.png" )
                                      , snd( "./resources/audio/boom.wav" ) {
    if ( player == nullptr ) {
        player = this;
    } // Seria bom lancar erro no else
    hp = PLAYER_HP;
    speed = Vec2( 0, 0 );
    Vec2 size = Vec2( bodySp.GetWidth(), bodySp.GetHeight() );
    box = Rect( pos - size/2, size );
    linearSpeed = 0;
    cannonAngle = 0;
    shootCooldown = Timer();
    // Permite ja dar um tiro logo assim que o jogo comeca
    shootCooldown.Update( P_SHOOT_COOLDOWN );
}

Penguins::~Penguins() {
    player = nullptr;
}

void Penguins::Update( float dt ) {
    shootCooldown.Update( dt );

    if ( (linearSpeed <= -PLAYER_MIN_SPEED) || (PLAYER_MIN_SPEED <= linearSpeed) ) {
        linearSpeed -= (linearSpeed >= 0 ? PLAYER_FRICTION : -PLAYER_FRICTION) * dt;
    }

    // Handle Input
    if ( IMinstance.IsMouseDown( LEFT_MOUSE_BUTTON ) ) {
        Shoot();
    }
    if ( IMinstance.IsKeyDown( W_KEY ) ) {
        linearSpeed += (PLAYER_ACCELERATION + PLAYER_FRICTION) * dt;
    }
    if ( IMinstance.IsKeyDown( S_KEY ) ) {
        linearSpeed -= (PLAYER_ACCELERATION + PLAYER_FRICTION) * dt;
    }
    if ( IMinstance.IsKeyDown( D_KEY ) ) {
        rotation += PLAYER_ROT_SPEED * dt;
    }
    if ( IMinstance.IsKeyDown( A_KEY ) ) {
        rotation -= PLAYER_ROT_SPEED * dt;
    }

    float actualSpeed = linearSpeed;
    if ( PLAYER_MAX_SPEED < linearSpeed ) {
        actualSpeed = linearSpeed = PLAYER_MAX_SPEED;
    } else if ( (-PLAYER_MIN_SPEED < linearSpeed) && (linearSpeed < PLAYER_MIN_SPEED) ) {
        actualSpeed = 0;
    } else if ( linearSpeed < -PLAYER_MAX_SPEED ) {
        actualSpeed = linearSpeed = -PLAYER_MAX_SPEED;
    }

    speed = Vec2::FromPolar( actualSpeed, rotation );
    Vec2 newPos = box.GetCentro() + speed * dt;
    
    Vec2 min( 0,0 );
    Vec2 max( 1408,1280 );
    newPos = Vec2( newPos.x < min.x ? min.x : newPos.x, newPos.y < min.y ? min.y : newPos.y );
    newPos = Vec2( newPos.x > max.x ? max.x : newPos.x, newPos.y > max.y ? max.y : newPos.y );
    newPos = newPos - box.GetTamanho()/2;

    box.SetPosicao( newPos );

    Vec2 mouseRelPos ( IMinstance.GetMouseX(), IMinstance.GetMouseY() );
    mouseRelPos = mouseRelPos - box.GetCentro() + Camera::pos;
    cannonAngle = mouseRelPos.GetRadianos();
}

void Penguins::Render( int cameraX, int cameraY ) {
    Vec2 boxPos = box.GetPosicao();
    bodySp.Render( boxPos.x - cameraX, boxPos.y - cameraY, rotation );
    cannonSp.Render( boxPos.x - cameraX, boxPos.y - cameraY, cannonAngle );
}

bool Penguins::IsDead() {
    if ( hp <= 0 ) {
        Camera::Unfollow();
        // Nao sei pq a sprite esta levemente desalinhada, esse -(50,10)
        // eh para corrigir. Obtido no olhometro
        Animation *anim = new Animation( box.GetCentro() - Vec2( 50, 10 ), rotation,
                                         "./resources/img/penguindeath.png", 5, 0.1, true );
        Game::GetInstance().GetCurrentState().AddObject( anim );
        snd.Play();
        return true;
    }
    return false;
}

void Penguins::NotifyCollision( GameObject const& other ) {
    if ( other.Is ( "Bullet" ) ) {
        Bullet b = dynamic_cast <Bullet const&> ( other );
        if ( b.targetsPlayer ) {
            hp -= b.GetDamage();
        }
    }
}

bool Penguins::Is( std::string type ) const {
    return "Penguins" == type;
}

void Penguins::Shoot() {
    if ( shootCooldown.Get() >= P_SHOOT_COOLDOWN ) {
        // Nao sei pq a sprite esta levemente desalinhada, esse -(17,5)
        // eh para corrigir. Obtido no olhometro
        Vec2 bulletPos = Vec2::FromPolar( P_BULLET_OFFSET, cannonAngle ) - Vec2( 17,5 );
        Bullet *b = new Bullet( box.GetCentro() + bulletPos, cannonAngle, BULLET_SPEED*1.2,
                                BULLET_REACH*2, "./resources/img/penguinbullet.png", false,
                                BULLET_DAMAGE, 4, 0.25 );
        Game::GetInstance().GetCurrentState().AddObject( b );
        shootCooldown.Restart();
    }
}
