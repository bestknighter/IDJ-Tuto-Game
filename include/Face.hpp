#ifndef _FACE_HPP_
#define _FACE_HPP_

class Face;

#include "GameObject.hpp"
#include "Sprite.hpp"

class Face : public GameObject {
  public:
    Face (float x, float y);
    void Damage (int damage); // Executa comportamento de quando se recebe dano
    void Update (float dt); // Atualiza posicao e vida
    void Render (int cameraX, int cameraY); // Renderiza na tela
    bool IsDead (); // TRUE se hitPoints <= 0, FALSE caso contrario
  private:
    int hitPoints; // Quantidade de pontos de vida que o objeto possui
    Sprite sp; // Imagem usada por esse objeto ao ser renderizado
};

#include <cstdlib>

#include "Camera.hpp"

#endif //_FACE_HPP_
