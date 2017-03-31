#include "State.hpp"

State::State () : bg (std::string ("./resources/img/ocean.jpg")) {
    quitRequested = false;
}

State::~State() {
    objectArray.clear ();
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::LoadAssets () {

}

void State::Update (float dt) {
    Input();
    for (int i = objectArray.size () - 1; i >= 0; --i) {
        if (objectArray[i]->IsDead ()) {
            objectArray.erase (objectArray.begin () + i);
        }
    }
}

void State::Render () {
    bg.Render (0, 0);
    for (unsigned int i = 0; i < objectArray.size (); ++i) {
        objectArray[i]->Render ();
    }
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    SDL_GetMouseState (&mouseX, &mouseY);
    while (SDL_PollEvent (&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            for (int i = objectArray.size () - 1; i >= 0; --i) {
                Face* face = (Face*) objectArray[i].get ();
                if(face->box.IsInside ((float)mouseX, (float)mouseY)) {
                    face->Damage (rand () % 10 + 10);
                    break;
                }
            }
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quitRequested = true;
            } else {
                AddObject ((float)mouseX, (float)mouseY);
            }
        }
    }
}

void State::AddObject (float mouseX, float mouseY) {
    Vec2 pos(mouseX, mouseY);
    Vec2 dir = Vec2::FromPolar (200, 2*3.141592*(float)rand ()/RAND_MAX);
    pos = pos + dir;
    objectArray.emplace_back (new Face (pos.x, pos.y));
}