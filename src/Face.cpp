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
    if (InputManager::GetInstance ().MousePress (LEFT_MOUSE_BUTTON) && box.IsInside (InputManager::GetInstance ().GetMouseX (), InputManager::GetInstance ().GetMouseY ())) {
        Damage (rand () % 10 + 10);
    }
}

void Face::Render () {
    sp.Render (box.x, box.y);
}

bool Face::IsDead () {
    return hitPoints <= 0;
}