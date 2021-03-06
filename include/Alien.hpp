#ifndef ALIEN_HPP
#define ALIEN_HPP

class Alien;

#define ALIEN_HP 50
#define ALIEN_SPEED 200 // Pixels/s

#include <queue>
#include <vector>

#include "GameObject.hpp"
#include "Minion.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"

#define ALIEN_ROT_SPEED 2*M_PI*0.033 // rad/s
#define ALIEN_MOVE_COOLDOWN 2 // s
#define ALIEN_SHOOT_COOLDOWN 0.2 //s

class Alien : public GameObject {
  public:
    Alien( Vec2 pos, int nMinions );
    ~Alien();
    
    static int alienCount;
    
    void Update( float dt );
    void Render( int cameraX, int cameraY );
    bool IsDead();
    void NotifyCollision( GameObject const& other );
    bool Is( std::string type ) const;
    void Shoot();

  private:
    enum AlienState { MOVING, RESTING };
    AlienState state;
    Timer restTimer;
    Timer shootTimer;
    Vec2 destination;
    Sprite sp; // Imagem do Alien
    Sound snd;
    Vec2 speed; // Velocidade de movimento
    int hp; // Quantidade de vida
    int minionArraySize;
    std::vector<Minion> minionArray; // Vetor de minions
    
    Minion& GetClosestMinion( Vec2 const& pos ); // Retorna minion mais proximo do ponto pos
};

#endif // ALIEN_HPP
