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


Rect Rect::operator- (Rect& other) {
    return Rect (
        x - other.x,
        y - other.y,
        w - other.w,
        h - other.h
    );
}

void Rect::Mover (Vec2& mov) {
    x += mov.x;
    y += mov.y;
}

void Rect::SetTamanho (Vec2& novoTamanho) {
    w = novoTamanho.x;
    h = novoTamanho.y;
}

Vec2 Rect::GetTamanho () {
    return Vec2 (w, h);
}

Vec2 Rect::GetPosicao () {
    return Vec2 (x, y);
}

Vec2 Rect::GetCentro () {
    return Vec2 ((x + w)/2, (y + h)/2);
}

bool Rect::isInside (Vec2& point) {
    return x <= point.x && point.x <= x+w && y <= point.y && point.y <= y+h;
}