#include "Rect.hpp"

Rect::Rect () {
    x = y = w = h = 0;
}

Rect::Rect (float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect::operator+ (Rect& other) {
    return Rect (
        x + other.x,
        y + other.y,
        w + other.w,
        h + other.h
    );
}


Rect Rect::operator+ (Rect& other) {
    return Rect (
        x - other.x,
        y - other.y,
        w - other.w,
        h - other.h
    );
}