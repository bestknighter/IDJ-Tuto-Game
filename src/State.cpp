#include "State.hpp"

State::State () : bg ("./resources/img/ocean.jpg") {
    tileSet = new TileSet (64, 64, "./resources/img/tileset.png");
    tileMap = new TileMap ("./resources/map/tileMap.txt", tileSet);
    quitRequested = false;
}

State::~State () {
    objectArray.clear ();
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::LoadAssets () {

}

void State::Update (float dt) {
    quitRequested = InputManager::GetInstance ().QuitRequested () || InputManager::GetInstance ().KeyPress (ESCAPE);
    if (InputManager::GetInstance ().IsKeyDown (SPACE)) {
        AddObject (InputManager::GetInstance ().GetMouseX (), InputManager::GetInstance ().GetMouseY ());
    }

    Camera::Update (dt);

    for (int i = objectArray.size () - 1; i >= 0; --i) {
        objectArray[i]->Update (dt);
        if (objectArray[i]->IsDead ()) {
            objectArray.erase (objectArray.begin () + i);
        }
    }
}

void State::Render () {
    bg.Render (Camera::pos.x, Camera::pos.y);
    tileMap->Render(Camera::pos.x, Camera::pos.y);
    for (unsigned int i = 0; i < objectArray.size (); ++i) {
        objectArray[i]->Render ();
    }
}

void State::AddObject (float mouseX, float mouseY) {
    Vec2 pos(mouseX, mouseY);
    Vec2 dir = Vec2::FromPolar (200, 2*3.141592*(float)rand ()/RAND_MAX);
    pos = pos + dir;
    objectArray.emplace_back (new Face (pos.x, pos.y));
}