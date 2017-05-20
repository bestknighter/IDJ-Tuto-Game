#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "Music.hpp"
#include "StateData.hpp"
#include "State.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

class EndState : public State {
  public:
    EndState(StateData stateData);

    void Update( float dt );
    void Render();

    void Pause();
    void Resume();
  private:
    Sprite bg;
    Music music;
    Text instruction;
};

#endif // ENDSTATE_HPP
