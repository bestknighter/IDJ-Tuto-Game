#include "Vec2.hpp"

Vec2::Vec2 () {
    x = y = 0;
}

Vec2::Vec2 (float x, float y) {
    this->x = x;
    this->y = y;
}

float Vec2::GetMagnitude () {
    return sqrt (pow (x, 2) + pow (y, 2));;
}

float Vec2::GetRadianos () {
    return atan2 (x, y);
}

Vec2 Vec2::FromPolar (float magnitude, float radianos) {
    return Vec2 (magnitude * cos (radianos), magnitude * sin (radianos));
}

Vec2 Vec2::operator+ (Vec2& other) {
    return Vec2 (x + other.x, y + other.y);
}

Vec2 Vec2::operator- (Vec2& other) {
    return Vec2 (x - other.x, y - other.y);
}

Vec2 Vec2::operator* (float other) {
    return Vec2 (x * other, y * other);
}

Vec2 Vec2::operator/ (float other) {
    return Vec2 (x / other, y / other);
}

Vec2 Vec2::GetNormal () {
    return Vec2 (x / magnitude, y / magnitude);
}

Vec2 Vec2::Rotate (float radianos) {
    return Vec2 (
        x * cos (radianos) - y * sin (radianos),
        y * cos (radianos) + x * sin (radianos)
    );
}

float Vec2::Dot (Vec2& lhs, Vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vec2::AnguloEntre (Vec2& lhs, Vec2& rhs) {
    return acos (Dot (lhs, rhs) / (lhs.magnitude * rhs.magnitude));
}
