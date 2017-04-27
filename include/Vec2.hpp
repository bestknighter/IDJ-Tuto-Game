#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#define M_PI 3.14159265358979323846264338327950288

class Vec2 {
  public:
    float x;
    float y;
    Vec2 ();
    Vec2 (float m);
    Vec2 (float x, float y);
    float GetMagnitude () const;
    float GetRadianos () const;
    // Gera um vetor a partir de coordenadas polares
    static Vec2 FromPolar (float magnitude, float radianos);
    Vec2 operator+ (Vec2 const& other) const;
    Vec2 operator- (Vec2 const& other) const;
    Vec2 operator* (float other) const;
    Vec2 operator/ (float other) const;
    Vec2 GetNormal () const;
    Vec2 Rotate (float radianos) const; // Rotaciona o vetor
    static float Dot (Vec2 const& lhs, Vec2 const& rhs); // Produto Vetorial
    static float AnguloEntre (Vec2 const& lhs, Vec2 const& rhs); // Produto Angular
};

#endif // _VEC2_HPP_
