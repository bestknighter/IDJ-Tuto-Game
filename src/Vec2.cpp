#include "Vec2.hpp"

Vec2::Vec2 () {
    x = y = 0;
}

Vec2::Vec2 (float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator+ (Vec2& other) {
    return Vec2 (x + other.x, y + other.y);
}

Vec2 Vec2::operator- (Vec2& other) {
    return Vec2 (x - other.x, y - other.y);
}