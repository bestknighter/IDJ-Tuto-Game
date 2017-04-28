#include "Penguins.hpp"

#include "Bullet.hpp"
#include "Game.hpp"
#include "InputManager.hpp"

Penguins* Penguins::player = nullptr;

Penguins::Penguins (Vec2 const& pos) : GameObject () {
    if (player == nullptr) {
        player = this;
    } // Seria bom lancar erro no else
    hp = PLAYER_HP;
    speed = Vec2 (0,0);
    bodySp = {"./resources/img/penguin.png"};
    cannonSp = {"./resources/img/cubngun.png"};
    Vec2 size = Vec2 (bodySp.GetWidth (), bodySp.GetHeight ());
    box = {pos - size/2, size};
    linearSpeed = 0;
    cannonAngle = 0;
}

Penguins::~Penguins () {
    player = nullptr;
}

void Penguins::Update (float dt) {
    if (IMinstance.MousePress (LEFT_MOUSE_BUTTON)) {
        Shoot ();
    }
    if (IMinstance.IsKeyDown (W_KEY)) {
        linearSpeed += PLAYER_ACCELERATION*dt;
    }
    if (IMinstance.IsKeyDown (S_KEY)) {
        linearSpeed -= PLAYER_ACCELERATION*dt;
    }
    if (IMinstance.IsKeyDown (D_KEY)) {
        rotation += PLAYER_ROT_SPEED*dt;
    }
    if (IMinstance.IsKeyDown (A_KEY)) {
        rotation -= PLAYER_ROT_SPEED*dt;
    }
    speed = Vec2::FromPolar (linearSpeed, rotation);
    box.SetPosicao (box.GetPosicao ()+speed*dt);

    cannonAngle = (Vec2 (IMinstance.GetMouseX (), IMinstance.GetMouseY ()) - box.GetCentro ()).GetRadianos ();
}

void Penguins::Render (int cameraX, int cameraY) {
    Vec2 boxPos = box.GetPosicao ();
    bodySp.Render (boxPos.x - cameraX, boxPos.y - cameraY, rotation);
    cannonSp.Render (boxPos.x - cameraX, boxPos.y - cameraY, cannonAngle);
}

bool Penguins::IsDead () {
    return hp < 0;
}

void Penguins::Shoot () {
    Vec2 bulletPos = Vec2::FromPolar (P_BULLET_OFFSET, cannonAngle);
    Bullet *b = new Bullet (box.GetCentro (), cannonAngle, BULLET_SPEED*1.1, BULLET_REACH*1.1, "./resources/img/penguinbullet.png", 4, 0.1);
    Game::GetInstance ().GetState ().AddObject (b);
}
