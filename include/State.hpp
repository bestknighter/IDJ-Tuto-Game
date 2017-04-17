#ifndef _STATE_HPP_
#define _STATE_HPP_

class State;

#include <vector>
#include <memory>

#ifdef _WIN32
    #include "SDL.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL.h"
#elif __unix__
    #include "SDL2/SDL.h"
#else
#   error "Unknown or unsupported compiler"
#endif

#include "Sprite.hpp"
#include "GameObject.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"

#define M_PI 3.14159265358979323846264338327950288

// Fase com os penguins
class State {
  public:
    State ();
    ~State ();
    bool QuitRequested ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();
  private:
    void AddObject (float mouseX, float mouseY); // Adiciona pinguim
    bool quitRequested;
    Sprite bg; // Plano de fundo
    std::vector<std::unique_ptr<GameObject>> objectArray; // Objetos dessa fase
    TileSet* tileSet; // Imagem com os tiles a ser usado no mapa
    TileMap* tileMap; // O mapa com os indices de cada tile a ser usado
};

#include <string>

#include "Vec2.hpp"
#include "Face.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"

#endif // _STATE_HPP_
