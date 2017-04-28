#include "Alien.hpp"

#include <cfloat>

#include "Bullet.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "Penguins.hpp"

int Alien::alienCount = 0;

Alien::Alien (Vec2 pos, int nMinions) : sp ("./resources/img/alien.png") {
    Vec2 size = Vec2 (sp.GetWidth (), sp.GetHeight ());
    box = Rect (pos - size/2, size);
    speed = {0,0};
    hp = ALIEN_HP*(1+nMinions*0.2); // Cada minion acrescenta 20% de hp base ao Alien
    restTimer = Timer ();
    state = AlienState::RESTING;
    
    for (int i = 0; i < nMinions; ++i) {
        minionArray.emplace_back (this, i*2*M_PI/nMinions);
    }

    ++alienCount;
}

Alien::~Alien () {
    --alienCount;
}

void Alien::Update (float dt) {
    // Handle Actions
    restTimer.Update (dt);
    switch (state) {
        case AlienState::RESTING: {
            if (restTimer.Get () > ALIEN_ACTION_COOLDOWN && nullptr != Penguins::player) {
                destination = Penguins::player->box.GetCentro ();
                Shoot (); // Comente isto e descomente acima para fazer o alien andar e atirar ao mesmo tempo
                state = AlienState::MOVING;
            }       
            break;
        }
        case AlienState::MOVING: {
            Vec2 moveDist = destination - box.GetCentro ();
            if (moveDist.GetMagnitude () <= ALIEN_SPEED*dt) {
                // Vai para a posicao final caso o que falte para andar seja menos do que a velocidade
                box.Mover (moveDist);
                state = AlienState::RESTING;
                restTimer.Restart ();
            } else {
                box.Mover ( moveDist.GetNormal ()*(ALIEN_SPEED*dt) );
            }
            break;
        }

        default:
            break;
    }
    
    // Handle minions and other stuff
    for (unsigned int i = 0; i < minionArray.size (); ++i) {
        minionArray[i].Update (dt);
    }

    rotation += ALIEN_ROT_SPEED*dt;
}

void Alien::Render (int cameraX, int cameraY) {
    sp.Render (box.GetPosicao ().x - cameraX, box.GetPosicao ().y - cameraY, rotation);
    for (unsigned int i = 0; i < minionArray.size (); ++i) {
        minionArray[i].Render (cameraX, cameraY);
    }
}

bool Alien::IsDead () {
    return hp <= 0;
}

void Alien::NotifyCollision (GameObject const& other) {
    if (other.Is ("Bullet")) {
        Bullet b = dynamic_cast <Bullet const&> (other);
        if (!b.targetsPlayer) {
            hp -= b.GetDamage ();
        }
    }
}

bool Alien::Is (std::string type) const {
    return "Alien" == type;
}

}

Minion& Alien::GetClosestMinion (Vec2 const& pos) {
    int closest = 0;
    float smallestDistance = FLT_MAX;
    for (unsigned int i = 0; i < minionArray.size (); ++i) {
        float distance = (pos - minionArray[i].box.GetPosicao ()).GetMagnitude ();
        if (distance < smallestDistance) {
            smallestDistance = distance;
            closest = i;
        }
    }
    return minionArray[closest];
}
