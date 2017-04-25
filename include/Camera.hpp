#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

class Camera;

#define BASE_CAM_SPEED 300

#include "Vec2.hpp"
#include "GameObject.hpp"

class Camera {
  public:
    static void Follow (GameObject* newFocus); // Permite setar um novo foco para a camera seguir
    static void Unfollow (); // Faz o controle da camera voltar a ser feito pelo usuario removendo o foco dela
    static void Update (float dt); // Atualiza a posicao da camera
    static Vec2 pos; // Posicao da camera
    static Vec2 speed; // Velocidade da camera
  private:
    static GameObject* focus; // Foco da camera
};

#endif // _CAMERA_HPP_
