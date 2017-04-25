#include "Alien.hpp"

Alien::Alien (float x, float y, int nMinions) : sp ("./resources/alien.png") {
    box = {x, y, sp.GetWidth (), sp.GetHeight ()};
    speed = {0,0};
    hp = ALIEN_HP;
    // for (int i = 0; i < nMinions; ++i) {
    //     Vec2 pos = Vec2::FromPolar (/*Distancia*/, i*2*M_PI/nMinions);
    //     minionArray.emplace_back (pos.x, pos.y);
    // }
}

Alien::~Alien () {

}

void Alien::Update (float dt) {

}

void Alien::Render () {

}

bool Alien::IsDead () {

}

