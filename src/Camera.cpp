#include "Camera.hpp"

#include "Game.hpp"
#include "InputManager.hpp"

Vec2 Camera::pos { 0, 0 };
Vec2 Camera::speed { 0, 0 };
bool Camera::following = true;
GameObject* Camera::focus = nullptr;

void Camera::Follow( GameObject* newFocus ) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update( float dt ) {
    // Trava/Destrava a camera no foco com a tecla SPACE
    following = IMinstance.KeyPress( SPACE_KEY ) ^ following;

    // Mover camera para cima com UP
    if ( IMinstance.IsKeyDown( UP_ARROW_KEY ) ) {
        speed = speed + Vec2( 0, -BASE_CAM_SPEED );
        following = false;
    }
    // Mover camera para baixo com DOWN
    if ( IMinstance.IsKeyDown( DOWN_ARROW_KEY ) ) {
        speed = speed + Vec2( 0, BASE_CAM_SPEED );
        following = false;
    }
    // Mover camera para direita com RIGHT
    if ( IMinstance.IsKeyDown( RIGHT_ARROW_KEY ) ) {
        speed = speed +  Vec2( BASE_CAM_SPEED, 0 );
        following = false;
    }
    // Mover camera para esquerda com LEFT
    if ( IMinstance.IsKeyDown( LEFT_ARROW_KEY ) ) {
        speed = speed + Vec2( -BASE_CAM_SPEED, 0 );
        following = false;
    }

    // Se a camera tiver um foco e for para segui-lo, posicione-a no centro daquele foco
    if ( (focus != nullptr) && following ) {
        pos = focus->box.GetCentro() - Game::GetInstance().GetScreenSize() / 2;
    } else { // Se nao, calcule a nova posicao da camera
        pos = pos + (speed * dt);
        speed = Vec2( 0, 0 );
    }
}
