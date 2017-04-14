#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

class Camera;

#include "Vec2.hpp"
#include "GameObject.hpp"

class Camera {
  public:
    static void Follow (GameObject* newFocus);
    static void Unfollow ();
    static void Update (float dt);
    static Vec2 pos;
    static Vec2 speed;
  private:
    static GameObject* focus;
};

#include "InputManager.hpp"

#endif // _CAMERA_HPP_
