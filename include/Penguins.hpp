#ifndef PENGUINS_HPP
#define PENGUINS_HPP

class Penguins;

#define PLAYER_HP 500
#define PLAYER_ACCELERATION 350 // Pixels/s^2
#define P_BULLET_OFFSET 65 // Pixels
#define P_SHOOT_COOLDOWN 0.8 // s
#define P_PRECISION_MOV_THRES 120 // Pixels/s
#define PLAYER_MAX_SPEED 500 // Pixels/s
#define PLAYER_MIN_SPEED 15 // Pixels/s
#define PLAYER_FRICTION 150 // Pixels/s^2

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"
#include "Timer.hpp"

#define PLAYER_ROT_SPEED 2*M_PI*0.45 // Rad/s

class Penguins : public GameObject {
  public:
    Penguins( Vec2 const& pos );
    ~Penguins();

    static Penguins* player;
    
    void Update( float dt );
    void Render( int cameraX, int cameraY );
    bool IsDead();
    void NotifyCollision( GameObject const& other );
    bool Is( std::string type ) const;
    void Shoot();
    
  private:
    Sprite bodySp;
    Sprite cannonSp;
    Vec2 speed;
    float linearSpeed;
    float cannonAngle;
    int hp;
    Timer shootCooldown;
};

#endif // PENGUINS_HPP
