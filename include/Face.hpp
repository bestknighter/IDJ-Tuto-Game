#ifndef _FACE_HPP_
#define _FACE_HPP_

class Face;

#include "GameObject.hpp"
#include "Sprite.hpp"

class Face : public GameObject {
  public:
    Face (float x, float y);
    void Damage (int damage);
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
  private:
    int hitPoints;
    Sprite sp;
};

#include <cstdlib>

#include "Camera.hpp"

#endif //_FACE_HPP_