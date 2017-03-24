#ifndef _VEC2_HPP_
#define _VEC2_HPP_

class Vec2 {
  public:
    float x;
    float y;
    Vec2 ();
    Vec2 (float x, float y);
    Vec2 operator+ (Vec2& other);
    Vec2 operator- (Vec2& other);
};

#endif //_VEC2_HPP_