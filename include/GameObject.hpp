#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

class GameObject;

#include <string>

#include "Rect.hpp"

class GameObject {
  public:
    GameObject ();
    virtual ~GameObject ();
    virtual void Update (float dt) = 0; // Atualiza o estado do objeto
    virtual void Render (int cameraX, int cameraY) = 0; // Renderiza esse objeto
    virtual bool IsDead () = 0;
    virtual void NotifyCollision (GameObject const& other) = 0; // Lida com colisao
    virtual bool Is (std::string type) const = 0; // Reflection bem primitivo
    Rect box; // Rect que armazena a posicao e as dimensoes do objeto
    float rotation;
};

#endif // _GAMEOBJECT_HPP_
