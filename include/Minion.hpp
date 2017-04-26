#ifndef _MINION_HPP_
#define _MINION_HPP_

class Minion;

#define DISTANCE_FROM_ALIEN 150

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

#define ARCSPEED -2*M_PI*0.15

class Minion : public GameObject {
  public:
    Minion (GameObject* minionCenter, float arcOffset);
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
    void Shoot (Vec2 const& target);
  private:
    GameObject* center;
    Sprite sp;
    float arc;
    float arcSpeed;
};

#endif // _MINION_HPP_
