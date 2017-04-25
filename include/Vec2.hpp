#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#define M_PI 3.14159265358979323846264338327950288

class Vec2 {
  public:
    float x;
    float y;
    Vec2 ();
    Vec2 (float x, float y);
    float GetMagnitude ();
    float GetRadianos ();
    // Gera um vetor a partir de coordenadas polares
    static Vec2 FromPolar (float magnitude, float radianos);
    Vec2 operator+ (Vec2& other);
    Vec2 operator- (Vec2& other);
    Vec2 operator* (float other);
    Vec2 operator/ (float other);
    Vec2 GetNormal ();
    Vec2 Rotate (float radianos); // Rotaciona o vetor
    static float Dot (Vec2& lhs, Vec2& rhs); // Produto Vetorial
    static float AnguloEntre (Vec2& lhs, Vec2& rhs); // Produto Angular
};

#include <cmath>

#endif //_VEC2_HPP_
