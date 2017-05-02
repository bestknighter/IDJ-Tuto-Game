#include "Collision.hpp"

#include <cmath>
#include <algorithm>

bool Collision::IsColliding( Rect const& a, Rect const& b, float angleOfA, float angleOfB ) {
    Vec2 aPos = a.GetPosicao();
    Vec2 aSize = a.GetTamanho();
    Vec2 A[] = {
        aPos + Vec2( 0, aSize.y ),
        aPos + aSize,
        aPos + Vec2( aSize.x, 0 ),
        aPos
    };
    
    Vec2 bPos = b.GetPosicao();
    Vec2 bSize = b.GetTamanho();
    Vec2 B[] = {
        bPos + Vec2( 0, bSize.y ),
        bPos + bSize,
        bPos + Vec2( bSize.x, 0 ),
        bPos
    };
    // Vec2 A[] e B[] sao arrays de vetores para cada ponta de cada Rect
    
    // Rotaciona os arrays
    for ( auto& v : A ) {
        v = (v - a.GetCentro()).Rotate( angleOfA ) + a.GetCentro();
    }

    for ( auto& v : B ) {
        v = (v - b.GetCentro()).Rotate( angleOfB ) + b.GetCentro();
    }

    Vec2 axes[] = {
        (A[0] - A[1]).GetNormal(),
        (A[1] - A[2]).GetNormal(),
        (B[0] - B[1]).GetNormal(),
        (B[1] - B[2]).GetNormal()
    };

    // Calcula eixo de separacao
    for ( auto& axis : axes ) {
        float P[4];

        for ( int i = 0; i < 4; ++i ) P[i] = Vec2::Dot( A[i], axis ); // Projetando no eixo

        float minA = *std::min_element( P, P + 4 );
        float maxA = *std::max_element( P, P + 4 );

        for ( int i = 0; i < 4; ++i ) P[i] = Vec2::Dot( B[i], axis ); // Projetando no eixo

        float minB = *std::min_element( P, P + 4 );
        float maxB = *std::max_element( P, P + 4 );

        if ( (maxA < minB) || (minA > maxB) ) {
            return false;
        }
    }

    return true;
}
