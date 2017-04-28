#ifndef _MINION_HPP_
#define _MINION_HPP_

class Minion;

#define DISTANCE_FROM_ALIEN 125 // Pixels

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

#define ARCSPEED -2*M_PI*0.10 // Rad/s

class Minion : public GameObject {
  public:
    Minion (GameObject* minionCenter, float arcOffset);
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
    void NotifyCollision (GameObject const& other);
    bool Is (std::string type) const;
    void Shoot (Vec2 const& target); // Atira um projetil em direcao a target
  private:
    GameObject* center; // Centro do Alien
    Sprite sp; // Imagem do minion
    float arc; // Rotacao ao redor de Alien
    float arcSpeed; // Velocidade da rotacao
};

#endif // _MINION_HPP_
