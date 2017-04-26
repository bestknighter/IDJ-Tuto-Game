#ifndef _ALIEN_HPP_
#define _ALIEN_HPP_

class Alien;

#define ALIEN_HP 50
#define ALIEN_SPEED 100

#include <queue>
#include <vector>

#include "GameObject.hpp"
#include "Minion.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

class Alien : public GameObject {
  public:
    Alien (Vec2 pos, int nMinions);
    ~Alien ();
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
  private:
    class Action {
      public:
        enum ActionType {
            MOVE,
            SHOOT
        };
        Action (ActionType type, Vec2 destination);
        ActionType type;
        Vec2 pos;
    };
    Sprite sp;
    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<Minion> minionArray;
};

#endif // _ALIEN_HPP_
