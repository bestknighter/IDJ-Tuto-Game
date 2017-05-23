#include "Minion.hpp"

#include <cstdlib> // std::rand() e RAND_MAX

#include "Bullet.hpp"
#include "Game.hpp"

Minion::Minion( GameObject* minionCenter, float arcOffset )
                : sp ( "./resources/img/minion.png" ) {
    center = minionCenter;
    arc = arcOffset;
    arcSpeed = ARCSPEED;
    sp.SetScale( Vec2( 1 + 0.5 * std::rand() / RAND_MAX ) );

    Update( 0 );
}

void Minion::Update( float dt ) {
    arc += arcSpeed * dt;
    rotation = arc - M_PI/2;

    // O centro do minion esta a uma distancia fixa e a um angulo fornecido do centro do alien
    Vec2 pos ( -sp.GetWidth() / 2, -sp.GetHeight() / 2);
    Vec2 posOffset = Vec2::FromPolar( DISTANCE_FROM_ALIEN, arc ) +
                     center->box.GetCentro();
    box.SetPosicao( pos+posOffset );
}

void Minion::Render( int cameraX, int cameraY ) {
    sp.Render( box.GetPosicao().x - cameraX, box.GetPosicao().y - cameraY, rotation );
}

bool Minion::IsDead() {
    return false; // Morre quando Alien morre
}

void Minion::Shoot( Vec2 const& pos ) {
    Bullet *b = new Bullet( box.GetCentro(), (pos - box.GetCentro()).GetRadianos(),
                            BULLET_SPEED, BULLET_REACH, "./resources/img/minionbullet2.png",
                            true, 1.5*BULLET_DAMAGE, 3, 0.1 );
    Game::GetInstance().GetCurrentState().AddObject( b );
}

void Minion::NotifyCollision( GameObject const& other __attribute__((unused)) ) {}

bool Minion::Is( std::string type ) const {
    return "Minion" == type;
}
