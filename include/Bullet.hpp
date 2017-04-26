#ifndef _BULLET_HPP_
#define _BULLET_HPP_

class Bullet;

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

class Bullet : public GameObject {
  public:
    Bullet (Vec2 pos, float angle, float speed, float maxDistance, std::string sprite);
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
  private:
    Sprite sp;
    Vec2 speed;
    float distanceLeft;
};

#endif // _BULLET_HPP_
