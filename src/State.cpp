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
    quitRequested = InputManager::GetInstance ().QuitRequested () || InputManager::GetInstance ().KeyPress (ESCAPE_KEY); // Sai dessa fase com ESC ou com solicitacoes do OS
    if (InputManager::GetInstance ().KeyPress (SPACE_KEY)) { // Pressionar a barra de espaco adiciona um pinguim
        AddObject (InputManager::GetInstance ().GetMouseX (), InputManager::GetInstance ().GetMouseY ());
    }

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

// void State::AddObject (float mouseX, float mouseY) {
//     Vec2 pos(mouseX, mouseY);
//     Vec2 dir = Vec2::FromPolar (200, 2*M_PI*(float)rand ()/RAND_MAX); // Gera um vetor deslocamento com modulo 200 e angulo aleatorio entre 0 e 2*PI
//     pos = pos + dir + Camera::pos;
//     objectArray.emplace_back (new Face {pos.x, pos.y});
// }
