#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Alien.hpp"

#include "Camera.hpp"
#include "InputManager.hpp"

Alien::Alien (Vec2 pos, int nMinions) : sp ("./resources/img/alien.png") {
    box = Rect ( pos, Vec2 (sp.GetWidth (), sp.GetHeight ()) );
    speed = {0,0};
    hp = ALIEN_HP;
    for (int i = 0; i < nMinions; ++i) {
        minionArray.emplace_back (this, i*2*M_PI/nMinions);
    }
}

Alien::~Alien () {
    
}

void Alien::Update (float dt) {
    if (IMinstance.MousePress (LEFT_MOUSE_BUTTON)) {
        taskQueue.emplace (Action::ActionType::SHOOT, Vec2 (IMinstance.GetMouseX () + Camera::pos.x, IMinstance.GetMouseY () + Camera::pos.y));
    }
    if (IMinstance.MousePress (RIGHT_MOUSE_BUTTON)) {
        taskQueue.emplace (Action::ActionType::MOVE, Vec2 (IMinstance.GetMouseX () + Camera::pos.x, IMinstance.GetMouseY () + Camera::pos.y));
    }
    if (!taskQueue.empty ()) {
        Action current = taskQueue.front ();
        switch (current.type) {
            case Action::ActionType::MOVE : {
                Vec2 moveDist = current.pos - box.GetCentro ();
                if (moveDist.GetMagnitude () <= ALIEN_SPEED*dt) {
                    box.Mover (moveDist);
                    taskQueue.pop ();
                } else {
                    box.Mover ( moveDist.GetNormal ()*(ALIEN_SPEED*dt) );
                }
                break;
            }
            case Action::ActionType::SHOOT : {
                // TODO atirar
                taskQueue.pop ();
                break;
            }
        }
    }
    for (unsigned int i = 0; i < minionArray.size (); ++i) {
        minionArray[i].Update (dt);
    }
}

void Alien::Render (int cameraX, int cameraY) {
    sp.Render (box.GetPosicao ().x - cameraX, box.GetPosicao ().y - cameraY);
    for (unsigned int i = 0; i < minionArray.size (); ++i) {
        minionArray[i].Render (cameraX, cameraY);
    }
}

bool Alien::IsDead () {
    return hp <= 0;
}

Alien::Action::Action (ActionType type, Vec2 destination) {
    this->type = type;
    pos = destination;
}

#pragma GCC diagnostic pop
