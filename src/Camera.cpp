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

    }
}
