#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <cfloat>

#include "Alien.hpp"

#include "Camera.hpp"
#include "InputManager.hpp"

Alien::Alien (Vec2 pos, int nMinions) : sp ("./resources/img/alien.png") {
    Vec2 size = Vec2 (sp.GetWidth (), sp.GetHeight ());
    box = Rect (pos - size/2, size);
    speed = {0,0};
    hp = ALIEN_HP;
    
    for (int i = 0; i < nMinions; ++i) {
        minionArray.emplace_back (this, i*2*M_PI/nMinions);
    }
}

Alien::~Alien () {
    
}

void Alien::Update (float dt) {
    // Handle Input
    {
        Vec2 posMouse = Vec2 (IMinstance.GetMouseX () + Camera::pos.x, IMinstance.GetMouseY () + Camera::pos.y);

        if (IMinstance.MousePress (LEFT_MOUSE_BUTTON)) {
            taskQueue.emplace (Action::ActionType::SHOOT, posMouse);
            taskQueue.push (taskQueue.front ()); // Grantindo que SHOOT sempre sera o primeiro item na fila
            taskQueue.pop ();
        }
        
        if (IMinstance.MousePress (RIGHT_MOUSE_BUTTON)) {
            if (!taskQueue.empty () && taskQueue.back ().type == Action::ActionType::MOVE) {
                taskQueue.back ().pos = posMouse; // Caso  a ultima acao seja de mover, simplemente atualize o destino
            } else {
                taskQueue.emplace (Action::ActionType::MOVE, posMouse);
            }
        }
    }

    // Handle Task Queue
    if (!taskQueue.empty ()) {
        Action current = taskQueue.front ();

        switch (current.type) {
            case Action::ActionType::MOVE:
            {
                Vec2 moveDist = current.pos - box.GetCentro ();
                if (moveDist.GetMagnitude () <= ALIEN_SPEED*dt) {
                    box.Mover (moveDist);
                    taskQueue.pop ();
                } else {
                    box.Mover ( moveDist.GetNormal ()*(ALIEN_SPEED*dt) );
                }
                break;
            }

            case Action::ActionType::SHOOT:
            {
                GetClosestMinion (current.pos).Shoot (current.pos);
                taskQueue.pop ();
                break;
            }

            default:
                break;
        }
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

Alien::Action::Action (ActionType type, Vec2 destination) {
    this->type = type;
    pos = destination;
}

Minion& Alien::GetClosestMinion (Vec2 const& pos) {
    int closest = 0;
    float smallestDistance = FLT_MAX;
    for (int i = 0; i < minionArray.size (); ++i) {
        float distance = (pos - minionArray[i].box.GetPosicao ()).GetMagnitude ();
        if (distance < smallestDistance) {
            smallestDistance = distance;
            closest = i;
        }
    }
    return minionArray[closest];
}

#pragma GCC diagnostic pop
