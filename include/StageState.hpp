#ifndef STAGESTATE_HPP
#define STAGESTATE_HPP

class StageState;

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
#include "Music.hpp"
#include "Sprite.hpp"
#include "State.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"

// Fase com os penguins
class StageState : public State {
  public:
    StageState();
    ~StageState();

    void LoadAssets();
    void Update( float dt );
    void Render();

    void Pause();
    void Resume();
  private:
    Sprite bg; // Plano de fundo
    Music ms;
    TileSet* tileSet; // Imagem com os tiles a ser usado no mapa
    TileMap* tileMap; // O mapa com os indices de cada tile a ser usado
};

#endif // STAGESTATE_HPP
