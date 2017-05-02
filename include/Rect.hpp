#ifndef RECT_HPP
#define RECT_HPP

class Rect;

#include "Vec2.hpp"

class Rect {
  public:
    Rect();
    Rect( Vec2 const& pos, Vec2 const& size );

    Rect operator+( Rect const& other ) const;
    Rect operator-( Rect const& other ) const;
    void Mover( Vec2 const& mov ); // Move o Rect sendo que mov eh o vetor deslocamento
    void SetTamanho( Vec2 const& novoTamanho ); // Seta novoTamanho como sendo o novo tamanho do Rect
    Vec2 const& GetTamanho() const;
    void SetPosicao( Vec2 const& novoPos );
    Vec2 const& GetPosicao() const;
    Vec2 GetCentro() const;
    bool IsInside( Vec2 const& point ) const; // True se o point esta dentro
    
  private:
    Vec2 pos;
    Vec2 size;
};

#endif // RECT_HPP
