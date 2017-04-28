#include "Rect.hpp"

Rect::Rect () : pos(), size() {

}

Rect::Rect (Vec2 const& pos, Vec2 const& size) {
    this->pos = pos;
    this->size = size;
}

Rect Rect::operator+ (Rect const& other) const {
    return Rect (pos + other.pos, size + other.size);
}

Rect Rect::operator- (Rect const& other) const {
    return Rect (pos - other.pos, size - other.size);
}

void Rect::Mover (Vec2 const& mov) {
    pos = pos + mov;
}

void Rect::SetTamanho (Vec2 const& novoTamanho) {
    size = novoTamanho;
}

Vec2 const& Rect::GetTamanho () const {
    return size;
}

Vec2 const& Rect::GetPosicao () const {
    return pos;
}

void Rect::SetPosicao (Vec2 const& novoPos) {
    pos = novoPos;
}

Vec2 Rect::GetCentro () const {
    return pos + (size/2);
}

bool Rect::IsInside (Vec2 const& point) const {
    return pos.x <= point.x && point.x <= pos.x+size.x && pos.y <= point.y && point.y <= pos.y+size.y;
}
