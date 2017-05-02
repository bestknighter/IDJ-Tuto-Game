#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet;

#define BULLET_SPEED 250 // Pixels/s
#define BULLET_REACH 1000 // Pixels
#define BULLET_DAMAGE 25

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

class Bullet : public GameObject {
  public:
    Bullet( Vec2 pos, float angle, float speed, float maxDistance,
            std::string sprite, bool targetsPlayer, float damage = BULLET_DAMAGE,
            unsigned int frameCount = 1, float frameTime = 0.2 );
    
    bool targetsPlayer; // Verdadeiro se esse eh um projetil inimigo
    
    void Update( float dt );
    void Render( int cameraX, int cameraY );
    bool IsDead();
    void NotifyCollision( GameObject const& other );
    bool Is( std::string type ) const;
    float GetDamage() const; // Retorna o dano desse projetil

  private:
    Sprite sp; // Imagem do tiro
    Vec2 speed; // Velocidade do projetil
    float distanceLeft; // "Tempo" de vida restante do projetil
    bool collided; // Verdadeiro se tiver atingido o alvo
    float damage; // Dano desse projetil
};

#endif // BULLET_HPP
