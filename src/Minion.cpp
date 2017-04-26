#include "Minion.hpp"

#include <cstdio>

Minion::Minion (GameObject* minionCenter, float arcOffset) : sp ("./resources/img/minion.png") {
    center = minionCenter;
    arc = arcOffset;
    Vec2 pos (-sp.GetWidth ()/2, -sp.GetHeight ()/2);
    Vec2 posOffset = Vec2::FromPolar (DISTANCE_FROM_ALIEN, arcOffset) + minionCenter->box.GetCentro ();
    box = Rect (pos+posOffset, Vec2 (sp.GetWidth (), sp.GetHeight ()));
    arcSpeed = ARCSPEED;
}

void Minion::Update (float dt) {
    Vec2 pos (-sp.GetWidth ()/2, -sp.GetHeight ()/2);
    arc += arcSpeed*dt;
    Vec2 posOffset = Vec2::FromPolar (DISTANCE_FROM_ALIEN, arc) + center->box.GetCentro ();
    box.SetPosicao (pos+posOffset);
}

void Minion::Render (int cameraX, int cameraY) {
    sp.Render (box.GetPosicao ().x - cameraX, box.GetPosicao ().y - cameraY);
}

bool Minion::IsDead () {
    return false;
}

void Minion::Shoot (Vec2 const& pos) {

}