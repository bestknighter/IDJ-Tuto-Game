#include "Camera.hpp"

#include "Game.hpp"
#include "InputManager.hpp"

Vec2 Camera::pos {0,0};
Vec2 Camera::speed {0,0};
bool Camera::following = true;
GameObject* Camera::focus = nullptr;

void Camera::Follow (GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow () {
    focus = nullptr;
}

void Camera::Update (float dt) {
    following = IMinstance.KeyPress (SPACE_KEY) ^ following; // Trava/Destrava a camera no foco com a tecla SPACE

    if (IMinstance.IsKeyDown (UP_ARROW_KEY)) { // Mover camera para cima com UP
        speed = speed + Vec2 (0, -BASE_CAM_SPEED);
        following = false;
    }
    if (IMinstance.IsKeyDown (DOWN_ARROW_KEY)) { // Mover camera para baixo com DOWN
        speed = speed + Vec2 (0, BASE_CAM_SPEED);
        following = false;
    }
    if (IMinstance.IsKeyDown (RIGHT_ARROW_KEY)) { // Mover camera para direita com RIGHT
        speed = speed +  Vec2 (BASE_CAM_SPEED, 0);
        following = false;
    }
    if (IMinstance.IsKeyDown (LEFT_ARROW_KEY)) { // Mover camera para esquerda com LEFT
        speed = speed + Vec2 (-BASE_CAM_SPEED, 0);
        following = false;
    }

    if (focus != nullptr && following) { // Se a camera tiver um foco e for para segui-lo, posicione-a no centro daquele foco
        pos = focus->box.GetCentro () - Game::GetInstance ().GetScreenSize ()/2;
    } else { // Se nao, calcule a nova posicao da camera
        pos = pos + (speed*dt);
        speed = {0,0};
    }
}
