#include "Alien.hpp"

#include <cstdlib>
#include <cfloat>

#include "Animation.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "Penguins.hpp"

int Alien::alienCount = 0;

Alien::Alien( Vec2 pos, int nMinions ) : sp( "./resources/img/alien.png" )
                                       , snd( "./resources/audio/boom.wav" ) {
    Vec2 size = Vec2( sp.GetWidth(), sp.GetHeight() );
    box = Rect( pos - size/2, size );
    speed = Vec2( 0, 0 );
    hp = ALIEN_HP * (1 + nMinions * 0.2); // Cada minion acrescenta 20% de hp base ao Alien
    restTimer = Timer();
    shootTimer = Timer();
    state = AlienState::RESTING;
    minionArraySize = nMinions;
    
    for ( int i = 0; i < nMinions; ++i ) {
        minionArray.emplace_back( this, i*2*M_PI/nMinions );
    }

    alienCount++;
}

Alien::~Alien() {
    minionArray.clear();
    alienCount--;
}

void Alien::Update( float dt ) {
    // Handle Actions
    restTimer.Update( dt );
    shootTimer.Update( dt );

    // Aqui ele atira constantemente
    // Shoot();

    switch ( state ) {
        case AlienState::RESTING: {
            if ( restTimer.Get() > ALIEN_MOVE_COOLDOWN*minionArraySize/2 && nullptr != Penguins::player ) {
                float noiseX = 150*2*(rand()/RAND_MAX-0.5);
                float noiseY = 150*2*(rand()/RAND_MAX-0.5);
                Vec2 noise( noiseX, noiseY );
                destination = Penguins::player->box.GetCentro() + noise;
                
                Vec2 min( 0,0 );
                Vec2 max( 1408,1280 );
                destination = Vec2( destination.x < min.x ? min.x : destination.x, destination.y < min.y ? min.y : destination.y );
                destination = Vec2( destination.x > max.x ? max.x : destination.x, destination.y > max.y ? max.y : destination.y );
                // Aqui ele atira assim que for voltar a andar
                // Shoot();
                state = AlienState::MOVING;
            }
            // Aqui ele atira enquanto estiver parado
            Shoot();
            break;
        }
        case AlienState::MOVING: {
            Vec2 moveDist = destination - box.GetCentro();
            if ( moveDist.GetMagnitude() <= ALIEN_SPEED * dt ) {
                // Vai para a posicao final caso o que falte para andar seja menos do que a velocidade
                box.Mover( moveDist );
                state = AlienState::RESTING;
                // Aqui ele atira assim que para de andar
                // Shoot();
                restTimer.Restart();
            } else {
                box.Mover( moveDist.GetNormal() * (ALIEN_SPEED * dt) );
            }
            // Aqui ele atira enquanto anda
            // Shoot();
            break;
        }

        default: {
            break;
        }
    }
    
    // Handle minions and other stuff
    for ( unsigned int i = 0; i < minionArray.size(); ++i ) {
        minionArray[i].Update( dt );
    }

    rotation += ALIEN_ROT_SPEED * dt;
}

void Alien::Render( int cameraX, int cameraY ) {
    sp.Render( box.GetPosicao().x - cameraX, box.GetPosicao().y - cameraY, rotation );
    for ( unsigned int i = 0; i < minionArray.size(); ++i ) {
        minionArray[i].Render( cameraX, cameraY );
    }
}

bool Alien::IsDead() {
    if ( hp <= 0 ) {
        // Nao sei pq a sprite esta levemente desalinhada, esse -(50,10) eh para corrigir. Obtido no olhometro 
        Animation *anim = new Animation( box.GetCentro() - Vec2(50, 10), rotation,
                                         "./resources/img/aliendeath.png", 4, 0.1, true );
        Game::GetInstance().GetCurrentState().AddObject( anim );
        
        for ( unsigned int i = 0; i < minionArray.size(); ++i ) {
            Vec2 pos = minionArray[i].box.GetCentro();
            float rotation = minionArray[i].rotation;
            anim = new Animation ( pos, rotation, "./resources/img/miniondeath.png", 4, 0.1, true );
            Game::GetInstance().GetCurrentState().AddObject( anim );
        }
        snd.Play();
        return true;
    }
    return false;
}

void Alien::NotifyCollision( GameObject const& other ) {
    if ( other.Is( "Bullet" ) ) {
        Bullet b = dynamic_cast<Bullet const&>( other );
        if ( !b.targetsPlayer ) {
            hp -= b.GetDamage();
        }
    }
}

bool Alien::Is( std::string type ) const {
    return "Alien" == type;
}

void Alien::Shoot() {
    if ( shootTimer.Get() > ALIEN_SHOOT_COOLDOWN ) {
        // So atira se existir pelo menos um minion para fazer isso
        if ( minionArray.size() > 0 && nullptr != Penguins::player ) {
            GetClosestMinion(
                Penguins::player->box.GetCentro() ).Shoot( Penguins::player->box.GetCentro() );
        }
        shootTimer.Restart();
    }
}

Minion& Alien::GetClosestMinion( Vec2 const& pos ) {
    int closest = 0;
    float smallestDistance = FLT_MAX;

    for ( unsigned int i = 0; i < minionArray.size (); ++i ) {
        float distance = (pos - minionArray[i].box.GetPosicao()).GetMagnitude();
        if ( distance < smallestDistance ) {
            smallestDistance = distance;
            closest = i;
        }
    }

    return minionArray[closest];
}
