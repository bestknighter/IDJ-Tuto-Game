#include "Face.hpp"

Face::Face (float x, float y) : sp ("./resources/img/penguinface.png") {
    float dx = sp.GetWidth ();
    float dy = sp.GetHeight ();
    box = Rect (x - dx/2, y - dy/2, dx, dy);
    hitPoints = 30;
}

void Face::Damage (int damage) {
    hitPoints -= damage;
}

void Face::Update (float dt) {
    int posX = InputManager::GetInstance ().GetMouseX () + Camera::pos.x;
    int posY = InputManager::GetInstance ().GetMouseY () + Camera::pos.y;
    if (InputManager::GetInstance ().MousePress (LEFT_MOUSE_BUTTON) && box.IsInside (posX, posY)) {
        Damage (rand () % 10 + 10);
    }
}

void Face::Render (int cameraX, int cameraY) {
    sp.Render (box.x-cameraX, box.y-cameraY);
}

bool Face::IsDead () {
    return hitPoints <= 0;
}