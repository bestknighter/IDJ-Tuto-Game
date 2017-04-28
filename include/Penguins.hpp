#ifndef _PENGUINS_HPP_
#define _PENGUINS_HPP_

class Penguins;

#define PLAYER_HP 500
#define PLAYER_ACCELERATION 250 // Pixels/s^2
#define P_BULLET_OFFSET 65 // Pixels
#define P_SHOOT_COOLDOWN 1 // s

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"
#include "Timer.hpp"

#define PLAYER_ROT_SPEED 2*M_PI*0.25 // Rad/s

class Penguins : public GameObject {
  public:
    Penguins (Vec2 const& pos);
    ~Penguins ();
    void Update (float dt);
    void Render (int cameraX, int cameraY);
    bool IsDead ();
    void NotifyCollision (GameObject const& other);
    bool Is (std::string type) const;
    void Shoot ();
    static Penguins* player;
  private:
    Sprite bodySp;
    Sprite cannonSp;
    Vec2 speed;
    float linearSpeed;
    float cannonAngle;
    int hp;
    Timer shootCooldown;
};

#endif // _PENGUINS_HPP_
