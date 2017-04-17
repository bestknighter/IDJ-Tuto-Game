#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

class GameObject;

#include "Rect.hpp"

class GameObject {
  public:
    virtual ~GameObject ();
    virtual void Update (float dt) = 0; // Atualiza o estado do objeto
    virtual void Render (int cameraX, int cameraY) = 0; // Renderiza esse objeto
    virtual bool IsDead () = 0;
    Rect box; // Rect que armazena a posicao e as dimensoes do objeto
};

#endif // _GAMEOBJECT_HPP_
