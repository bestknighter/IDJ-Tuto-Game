#include "Animation.hpp"

Animation::Animation (Vec2 pos, float rotation, Sprite const& sprite, float timeLimit, bool ends) {
    this->rotation = rotation;
    this->timeLimit = timeLimit;
    oneTimeOnly = ends;
    sp = sprite;

    Vec2 size (sp.GetWidth (), sp.GetHeight ());
    box = {pos-size/2, size};
}

void Animation::Update (float dt) {
    endTimer.Update (dt);
    sp.Update (dt);
}

void Animation::Render (int cameraX, int cameraY) {
    sp.Render (box.GetPosicao ().x - cameraX, box.GetPosicao ().y - cameraY, rotation);
}

bool Animation::IsDead () {
    return oneTimeOnly && endTimer.Get () > timeLimit;
}

void Animation::NotifyCollision (GameObject const&  other) {
    // Nada mesmo
}

bool Animation::Is (std::string type) const {
    return "Animation" == type;
}
