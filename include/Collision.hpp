#ifndef _COLLISION_HPP_
#define _COLLISION_HPP_

#include "Rect.hpp"

class Collision {
    public:
        // Metodo AABB de deteccao de colisao
        bool static IsColliding(Rect const& a, Rect const& b, float angleOfA, float angleOfB);
};

#endif // _COLLISION_HPP_
