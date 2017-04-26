#include "Bullet.hpp"

Bullet::Bullet (Vec2 pos, float angle, float speed, float maxDistance, std::string sprite) : sp(sprite) {
    distanceLeft = maxDistance;
    speed = Vec2::FromPolar (speed, angle);
    box = {pos, sp.GetTamanho ()};
}

void Bullet::Update (float dt) {

}

void Bullet::Render (int cameraX, int cameraY) {

}

vool Bullet::IsDead () {

}
