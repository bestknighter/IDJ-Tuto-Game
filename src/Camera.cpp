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
    if (focus != nullptr) {
        pos = focus->box.GetCentro ();
    } else {
        Vec2 newSpeed;
        if (InputManager::GetInstance ().IsKeyDown (UP_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (W_KEY)) {
            newSpeed = {0, -BASE_CAM_SPEED};
            speed = speed + newSpeed;
        }
        if (InputManager::GetInstance ().IsKeyDown (DOWN_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (S_KEY)) {
            newSpeed = {0, BASE_CAM_SPEED};
            speed = speed + newSpeed;
        }
        if (InputManager::GetInstance ().IsKeyDown (RIGHT_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (D_KEY)) {
            newSpeed = {BASE_CAM_SPEED, 0};
            speed = speed + newSpeed;
        }
        if (InputManager::GetInstance ().IsKeyDown (LEFT_ARROW_KEY) || InputManager::GetInstance ().IsKeyDown (A_KEY)) {
            newSpeed = {-BASE_CAM_SPEED, 0};
            speed = speed + newSpeed;
        }
        pos = {pos.x+speed.x*dt, pos.y+speed.y*dt};
        speed = {0,0};
    }
}
