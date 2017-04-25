#include "Rect.hpp"

Rect::Rect () : pos(), size() {

}

Rect::Rect (Vec2 pos, Vec2 size) {
    this->pos = pos;
    this->size = size;
}

Rect Rect::operator+ (Rect const& other) {
    return Rect (pos + other.pos, size + other.size);
}

Rect Rect::operator- (Rect const& other) {
    return Rect (pos - other.pos, size - other.size);
}

void Rect::Mover (Vec2 const& mov) {
    pos = pos + mov;
}

void Rect::SetTamanho (Vec2 const& novoTamanho) {
    size = novoTamanho;
}

Vec2 Rect::GetTamanho () {
    return size;
}

Vec2 Rect::GetPosicao () {
    return pos;
}

Vec2 Rect::GetCentro () {
    return pos + (size/2);
}

bool Rect::IsInside (Vec2 const& point) {
    return pos.x <= point.x && point.x <= pos.x+size.x && pos.y <= point.y && point.y <= pos.y+size.y;
}
