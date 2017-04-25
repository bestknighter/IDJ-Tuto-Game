#ifndef _ALIEN_HPP_
#define _ALIEN_HPP_

class Alien;

#include <queue>
#include <vector>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

#define ALIEN_HP 50

class Alien : GameObject {
  public:
    Alien (float x, float y, int nMinions);
    ~Alien ();
    void Update (float dt);
    void Render ();
    bool IsDead ();
  private:
    Sprite sp;
    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<Minion> minionArray;
    class Action {
      public:
        enum ActionType {
            MOVE,
            SHOOT
        };
        Action (ActionType type, float x, float y);
        ActionType type;
        Vec2 pos;
    };
};

#endif // _ALIEN_HPP_
