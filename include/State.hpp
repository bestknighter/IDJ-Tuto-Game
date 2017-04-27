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

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"

// Fase com os penguins
class State {
  public:
    State ();
    ~State ();
    bool QuitRequested ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();
    void AddObject (GameObject *ptr);
  private:
    // void AddObject (float mouseX, float mouseY); // Adiciona pinguim
    bool quitRequested;
    Sprite bg; // Plano de fundo
    std::vector<std::unique_ptr<GameObject>> objectArray; // Objetos dessa fase
    TileSet* tileSet; // Imagem com os tiles a ser usado no mapa
    TileMap* tileMap; // O mapa com os indices de cada tile a ser usado
};

#endif // _STATE_HPP_
