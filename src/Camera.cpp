#include "Camera.hpp"

Vec2 Camera::pos {0,0};
Vec2 Camera::speed {0,0};
GameObject* Camera::focus = nullptr;

void Camera::Follow (GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow () {
    focus = nullptr;
}

void Camera::Update (float dt) {
    if (focus != nullptr) { // Se a camera tiver um foco, posicione-a no centro daquele foco
        pos = focus->box.GetCentro ();
    } else { // Se nao, calcule a nova velocidade de movimento da camera baseado no teclado
        Vec2 newSpeed; // TODO Refatorar quando Vec2 estiver mais completo
        if (InputManager::GetInstance ().IsKeyDown (UP_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (W_KEY)) { // Mover camera para cima com UP ou W
            newSpeed = {0, -BASE_CAM_SPEED};
            speed = speed + newSpeed;
        }
        if (InputManager::GetInstance ().IsKeyDown (DOWN_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (S_KEY)) { // Mover camera para baixo com DOWN ou S
            newSpeed = {0, BASE_CAM_SPEED};
            speed = speed + newSpeed;
        }
        if (InputManager::GetInstance ().IsKeyDown (RIGHT_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (D_KEY)) { // Mover camera para direita com RIGHT ou D
            newSpeed = {BASE_CAM_SPEED, 0};
            speed = speed + newSpeed;
        }
        if (InputManager::GetInstance ().IsKeyDown (LEFT_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (A_KEY)) { // Mover camera para esquerda com LEFT ou A
            newSpeed = {-BASE_CAM_SPEED, 0};
            speed = speed + newSpeed;
        }
        pos = {pos.x+speed.x*dt, pos.y+speed.y*dt};
        speed = {0,0};
    }
}
