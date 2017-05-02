#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Rect.hpp"

class Collision {
    public:
        // Metodo AABB de deteccao de colisao
        bool static IsColliding( Rect const& a, Rect const& b, float angleOfA, float angleOfB );
};

#endif // COLLISION_HPP
