#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera;

#define BASE_CAM_SPEED 350 // Pixels/s

#include "Vec2.hpp"
#include "GameObject.hpp"

class Camera {
  public:
    static Vec2 pos; // Posicao da camera
    static Vec2 speed; // Velocidade da camera
    
    static void Follow( GameObject* newFocus ); // Permite setar um novo foco para a camera seguir
    static void Unfollow(); // Faz o controle da camera voltar a ser feito pelo usuario removendo o foco dela
    static void Update( float dt ); // Atualiza a posicao da camera
    
  private:
    static bool following; // Verdadeiro se eh para continuar seguindo o foco
    static GameObject* focus; // Foco da camera
};

#endif // CAMERA_HPP
