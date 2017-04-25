#include "State.hpp"

#include <string>

#include "Alien.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Vec2.hpp"

State::State () : bg ("./resources/img/ocean.jpg") {
    tileSet = new TileSet (64, 64, "./resources/img/tileset.png");
    tileMap = new TileMap ("./resources/map/tileMap.txt", tileSet);
    quitRequested = false;
    objectArray.emplace_back (new Alien {{512, 300}, 0});
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
    quitRequested = IMinstance.QuitRequested () || IMinstance.KeyPress (ESCAPE_KEY); // Sai dessa fase com ESC ou com solicitacoes do OS

    Camera::Update (dt);
    // Atualiza todos os objetos e remove os que ja estao mortos
    for (int i = objectArray.size () - 1; i >= 0; --i) {
        objectArray[i]->Update (dt);
        if (objectArray[i]->IsDead ()) {
            objectArray.erase (objectArray.begin () + i);
        }
    }
}

void State::Render () {
    bg.Render (0,0);
    tileMap->Render(Camera::pos.x, Camera::pos.y, 0, 0); // Renderiza camada base do mapa
    for (unsigned int i = 0; i < objectArray.size (); ++i) { // Depois renderiza pinguins
        objectArray[i]->Render (Camera::pos.x, Camera::pos.y);
    }
    tileMap->Render(Camera::pos.x, Camera::pos.y, 1); // Por ultimo renderiza o resto do mapa
}
