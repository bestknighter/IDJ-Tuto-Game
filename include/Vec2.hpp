#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#include <cmath>

class Vec2 {
  public:
    float x;
    float y;
    Vec2 ();
    Vec2 (float x, float y);
    float GetMagnitude ();
    float GetRadianos ();
    static Vec2 FromPolar (float magnitude, float radianos);
    Vec2 operator+ (Vec2& other);
    Vec2 operator- (Vec2& other);
    Vec2 operator* (float other);
    Vec2 operator/ (float other);
    Vec2 GetNormal ();
    Vec2 Rotate (float radianos);
    static float Dot (Vec2& lhs, Vec2& rhs);
    static float AnguloEntre (Vec2& lhs, Vec2& rhs);
    static Vec2 i;
    static Vec2 j;
  private:
    float magnitude;
    float radianos;
};

#endif //_VEC2_HPP_