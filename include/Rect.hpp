#ifndef _RECT_HPP_
#define _RECT_HPP_

class Rect;

#include "Vec2.hpp"

class Rect {
  public:
    Rect ();
    Rect (Vec2 const& pos, Vec2 const& size);
    Rect operator+ (Rect const& other);
    Rect operator- (Rect const& other);
    void Mover (Vec2 const& mov); // Move o Rect sendo que mov eh o vetor deslocamento
    void SetTamanho (Vec2 const& novoTamanho); // Seta novoTamanho como sendo o novo tamanho do Rect
    Vec2 const& GetTamanho ();
    void SetPosicao (Vec2 const& novoPos);
    Vec2 const& GetPosicao ();
    Vec2 GetCentro ();
    bool IsInside (Vec2 const& point);
  private:
    Vec2 pos;
    Vec2 size;
};

#endif // _RECT_HPP_
