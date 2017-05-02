#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation;

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"

class Animation : public GameObject {
  public:
    Animation( Vec2 pos, float rotation, std::string sprite,
               unsigned int frameCount, float frameTime, bool ends );
    
    void Update( float dt );
    void Render( int cameraX, int cameraY );
    bool IsDead();
    void NotifyCollision( GameObject const& other );
    bool Is( std::string type ) const;
    
  private:
    Timer endTimer;
    float timeLimit;
    bool oneTimeOnly;
    Sprite sp;
};

#endif // ANIMATION_HPP
