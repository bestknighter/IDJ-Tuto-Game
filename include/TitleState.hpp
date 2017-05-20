#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include "Sprite.hpp"
#include "State.hpp"
#include "Text.hpp"

class TitleState : public State {
  public:
    TitleState();

    void Update( float dt );
    void Render();

    void Pause();
    void Resume();
  private:
    Sprite bg;
    Text titleText;
};

#endif // TITLESTATE_HPP
