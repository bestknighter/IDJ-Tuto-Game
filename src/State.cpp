#include "State.hpp"

#include "Camera.hpp"

State::State() {
    popRequested = false;
    quitRequested = false;
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {}

void State::AddObject( GameObject* object ) {
    objectArray.emplace_back( object );
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::UpdateArray( float dt ) {
    for ( int i = 0; i < objectArray.size(); ++i ) {
        objectArray[i]->Update( dt );
        if ( objectArray[i]->IsDead() ) {
            objectArray.erase( objectArray.begin() + i );
        }
    }
}

void State::RenderArray() {
    for ( unsigned int i = 0; i < objectArray.size(); ++i ) {
        objectArray[i]->Render( Camera::pos.x, Camera::pos.y );
    }
}
