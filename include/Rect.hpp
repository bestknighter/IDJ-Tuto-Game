#ifndef _RECT_HPP_
#define _RECT_HPP_

#include "Vec2.hpp"

class Rect {
  public:
    float x;
    float y;
    float w;
    float h;
    Rect ();
    Rect (float x, float y, float w, float h);
    Rect operator+ (Rect& other);
    Rect operator- (Rect& other);
    void Mover (Vec2& mov);
    void SetTamanho (Vec2& novoTamanho);
    Vec2 GetTamanho ();
    Vec2 GetPosicao ();
    Vec2 GetCentro ();
    bool isInside (Vec2& point);
};

#endif //_RECT_HPP_