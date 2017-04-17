#ifndef _RECT_HPP_
#define _RECT_HPP_

class Rect;

#include "Vec2.hpp"

class Rect {
  public:
    float x; // Posicao X
    float y; // Posicao Y
    float w; // Largura
    float h; // Altura
    Rect ();
    Rect (float x, float y, float w, float h);
    Rect operator+ (Rect& other);
    Rect operator- (Rect& other);
    void Mover (Vec2& mov); // Move o Rect sendo que mov eh o vetor deslocamento
    void SetTamanho (Vec2& novoTamanho); // Seta novoTamanho como sendo o novo tamanho do Rect
    Vec2 GetTamanho ();
    Vec2 GetPosicao ();
    Vec2 GetCentro ();
    bool IsInside (float x, float y);
    bool IsInside (Vec2& point);
};

#endif // _RECT_HPP_
