#ifndef VEC2_HPP
#define VEC2_HPP

#define M_PI 3.14159265358979323846264338327950288

class Vec2 {
  public:
    Vec2();
    Vec2( float m );
    Vec2( float x, float y );

    float x;
    float y;

    static Vec2 FromPolar( float magnitude, float radianos );
    static float Dot( Vec2 const& lhs, Vec2 const& rhs ); // Produto Vetorial
    static float AnguloEntre( Vec2 const& lhs, Vec2 const& rhs ); // Produto Angular

    float GetMagnitude() const;
    float GetRadianos() const;
    // Gera um vetor a partir de coordenadas polares
    Vec2 operator+( Vec2 const& other ) const;
    Vec2 operator-( Vec2 const& other ) const;
    Vec2 operator*( float other ) const;
    Vec2 operator/( float other ) const;
    Vec2 GetNormal() const; // Retorna uma versao normalizada
    Vec2 Rotate( float radianos ) const; // Rotaciona o vetor
};

#endif // VEC2_HPP
