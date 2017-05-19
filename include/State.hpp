#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include <memory>

#include "GameObject.hpp"

class State {
  public:
    State();
    ~State();

    virtual void LoadAssets() = 0;
    virtual void Update( float dt ) = 0;
    virtual void Render() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void AddObject( GameObject* object );

    bool PopRequested();
    bool QuitRequested();
  protected:
    virtual void UpdateArray( float dt );
    virtual void RenderArray();

    bool popRequested;
    bool quitRequested;
    
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif // STATE_HPP
