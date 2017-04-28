#ifndef _ALIEN_HPP_
#define _ALIEN_HPP_

class Alien;

#define ALIEN_HP 50
#define ALIEN_SPEED 100 // Pixels/s

#include <queue>
#include <vector>

#include "GameObject.hpp"
#include "Minion.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

#define ALIEN_ROT_SPEED 2*M_PI*0.033 // Rad/s

class Alien : public GameObject {
  public:
    Alien (Vec2 pos, int nMinions);
    ~Alien ();
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
    void NotifyCollision (GameObject const& other);
    bool Is (std::string type) const;
  private:
    class Action {
      public:
        enum ActionType {
            MOVE,
            SHOOT
        };
        Action (ActionType type, Vec2 destination);
        ActionType type;  // Tipo da acao
        Vec2 pos; // Destino do tiro/movimento
    };
    Sprite sp; // Imagem do Alien
    Vec2 speed; // Velocidade de movimento
    int hp; // Quantidade de vida
    std::queue<Action> taskQueue; // Fila de atividades para se cumprir
    std::vector<Minion> minionArray; // Vetor de minions
    Minion& GetClosestMinion (Vec2 const& pos); // Retorna minion mais proximo do ponto pos
};

#endif // _ALIEN_HPP_
