#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

class GameObject;

#include "Rect.hpp"

class GameObject {
  public:
    virtual ~GameObject ();
    virtual void Update (float dt) = 0;
    virtual void Render (int cameraX, int cameraY) = 0;
    virtual bool IsDead () = 0;
    Rect box;
};

#endif //_GAMEOBJECT_HPP_