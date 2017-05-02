#include "Vec2.hpp"

#include <cmath>

Vec2::Vec2() {
    x = y = 0;
}

Vec2::Vec2( float m ) {
    x = m;
    y = m;
}

Vec2::Vec2( float x, float y ) {
    this->x = x;
    this->y = y;
}

float Vec2::GetMagnitude() const {
    return sqrt( x * x + y * y );
}

float Vec2::GetRadianos() const {
    return atan2( y, x );
}

Vec2 Vec2::FromPolar( float magnitude, float radianos ) {
    return Vec2( magnitude * cos( radianos ), magnitude * sin( radianos ) );
}

Vec2 Vec2::operator+( Vec2 const& other ) const {
    return Vec2( x + other.x, y + other.y );
}

Vec2 Vec2::operator-( Vec2 const& other ) const {
    return Vec2( x - other.x, y - other.y );
}

Vec2 Vec2::operator*( float other ) const {
    return Vec2( x * other, y * other );
}

Vec2 Vec2::operator/( float other ) const {
    return Vec2( x / other, y / other );
}

Vec2 Vec2::GetNormal() const {
    float magnitude = GetMagnitude();
    return Vec2( x / magnitude, y / magnitude );
}

Vec2 Vec2::Rotate( float radianos ) const {
    return Vec2 ( x * cos ( radianos ) - y * sin ( radianos ),
                  y * cos ( radianos ) + x * sin ( radianos ) );
}

float Vec2::Dot( Vec2 const& lhs, Vec2 const& rhs ) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vec2::AnguloEntre( Vec2 const& lhs, Vec2 const& rhs ) {
    return acos( Dot( lhs, rhs ) / (lhs.GetMagnitude() * rhs.GetMagnitude()) );
}
