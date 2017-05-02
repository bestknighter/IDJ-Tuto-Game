#include "Bullet.hpp"

Bullet::Bullet( Vec2 pos, float angle, float speed, float maxDistance,
                std::string sprite, bool targetsPlayer, float damage,
                unsigned int frameCount, float frameTime )
                : sp ( sprite, frameCount, frameTime ) {
    distanceLeft = maxDistance;
    this->speed = Vec2::FromPolar( speed, angle );
    rotation = angle;
    this->damage = damage;
    this->targetsPlayer = targetsPlayer;

    Vec2 size ( sp.GetWidth(), sp.GetHeight() );
    box = Rect( pos-size/2, size );
    collided = false;
}

void Bullet::Update( float dt ) {
    box.Mover( speed * dt );
    distanceLeft -= (speed * dt).GetMagnitude();
    sp.Update( dt );
}

void Bullet::Render( int cameraX, int cameraY ) {
    sp.Render( box.GetPosicao().x - cameraX, box.GetPosicao().y - cameraY, rotation );
}

bool Bullet::IsDead() {
    return (distanceLeft <= 0) || collided;
}

void Bullet::NotifyCollision( GameObject const& other ) {
    collided = (!targetsPlayer && other.Is( "Alien" )) || (targetsPlayer && other.Is( "Penguins" ));
}

bool Bullet::Is( std::string type ) const {
    return "Bullet" == type;
}

float Bullet::GetDamage() const {
    return damage;
}
