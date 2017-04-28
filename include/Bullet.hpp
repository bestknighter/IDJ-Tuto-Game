#ifndef _BULLET_HPP_
#define _BULLET_HPP_

class Bullet;

#define BULLET_SPEED 250 // Pixels/s
#define BULLET_REACH 1000 // Pixels

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

class Bullet : public GameObject {
  public:
    Bullet (Vec2 pos, float angle, float speed, float maxDistance, std::string sprite, unsigned int frameCount = 1, float frameTime = 0.2);
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
  private:
    Sprite sp; // Imagem do tiro
    Vec2 speed; // Velocidade do projetil
    float distanceLeft; // "Tempo" de vida restante do projetil
};

#endif // _BULLET_HPP_
