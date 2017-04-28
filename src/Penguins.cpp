#include "Penguins.hpp"

#include "Animation.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
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
    shootCooldown = Timer ();
    shootCooldown.Update (P_SHOOT_COOLDOWN); // Permite ja dar um tiro logo assim que o jogo comeca
}

Penguins::~Penguins () {
    player = nullptr;
}

void Penguins::Update (float dt) {
    shootCooldown.Update (dt);

    // Handle Input
    if (IMinstance.MousePress (LEFT_MOUSE_BUTTON)) {
        if (shootCooldown.Get () >= P_SHOOT_COOLDOWN) {
            Shoot ();
            shootCooldown.Restart ();
        }
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

    Vec2 mouseRelPos (IMinstance.GetMouseX (), IMinstance.GetMouseY ());
    mouseRelPos = mouseRelPos - box.GetCentro () + Camera::pos;
    cannonAngle = mouseRelPos.GetRadianos ();
}

void Penguins::Render (int cameraX, int cameraY) {
    Vec2 boxPos = box.GetPosicao ();
    bodySp.Render (boxPos.x - cameraX, boxPos.y - cameraY, rotation);
    cannonSp.Render (boxPos.x - cameraX+17, boxPos.y - cameraY+5, cannonAngle); // Nao sei pq a sprite esta levemente desalinhada, esse (+17,+5) eh para corrigir. Obtido no olhometro
}

bool Penguins::IsDead () {
    if (hp <= 0) {
        Camera::Unfollow ();
        Sprite sp ("./resources/img/penguindeath.png", 5, 0.1);
        Animation *anim = new Animation (box.GetCentro () - Vec2 (50, 10), rotation, sp, 0.5, true); // Nao sei pq a sprite esta levemente desalinhada, esse -(50,10) eh para corrigir. Obtido no olhometro
        Game::GetInstance ().GetState ().AddObject (anim);
        return true;
    }
    return false;
}

void Penguins::NotifyCollision (GameObject const& other) {
    if (other.Is ("Bullet")) {
        Bullet b = dynamic_cast <Bullet const&> (other);
        if (b.targetsPlayer) {
            hp -= b.GetDamage ();
        }
    }
}

bool Penguins::Is (std::string type) const {
    return "Penguins" == type;
}

void Penguins::Shoot () {
    Vec2 bulletPos = Vec2::FromPolar (P_BULLET_OFFSET, cannonAngle);
    Bullet *b = new Bullet (box.GetCentro ()+bulletPos, cannonAngle, BULLET_SPEED*1.2, BULLET_REACH*2, "./resources/img/penguinbullet.png", false, BULLET_DAMAGE, 4, 0.25);
    Game::GetInstance ().GetState ().AddObject (b);
}
