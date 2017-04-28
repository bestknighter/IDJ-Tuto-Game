#include "Bullet.hpp"

Bullet::Bullet (Vec2 pos, float angle, float speed, float maxDistance, std::string sprite, unsigned int frameCount, float frameTime) : sp(sprite, frameCount, frameTime) {
    distanceLeft = maxDistance;
    this->speed = Vec2::FromPolar (speed, angle);
    rotation = angle;

    Vec2 size (sp.GetWidth (), sp.GetHeight ());
    box = {pos-size/2, size};
}

void Bullet::Update (float dt) {
    box.Mover (speed*dt);
    distanceLeft -= (speed*dt).GetMagnitude ();
    sp.Update (dt);
}

void Bullet::Render (int cameraX, int cameraY) {
    sp.Render (box.GetPosicao ().x - cameraX, box.GetPosicao ().y - cameraY, rotation);
}

bool Bullet::IsDead () {
    return distanceLeft <= 0;
}
