#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject;

#include <string>

#include "Rect.hpp"

class GameObject {
  public:
    GameObject();
    virtual ~GameObject();
    
    Rect box; // Rect que armazena a posicao e as dimensoes do objeto
    float rotation;

    virtual void Update( float dt ) = 0; // Atualiza o estado do objeto
    virtual void Render( int cameraX, int cameraY ) = 0; // Renderiza esse objeto
    virtual bool IsDead() = 0;
    virtual void NotifyCollision( GameObject const& other ) = 0; // Lida com colisao
    virtual bool Is( std::string type ) const = 0; // Reflection bem primitivo
};

#endif // GAMEOBJECT_HPP
