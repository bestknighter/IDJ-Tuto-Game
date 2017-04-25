#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "InputManager.hpp"

void InputManager::Update () {
    SDL_Event event;
    SDL_GetMouseState (&mouseX, &mouseY);
    quitRequested = false;
    ++updateCounter;
    while (SDL_PollEvent (&event)) { // Executa o loop enquanto tiver evento para lidar
        switch (event.type) { // Muda o comportamento de acordo com o tipo do evento
            case SDL_KEYDOWN:
                if (event.key.repeat) continue; // Nao precisa registrar repeticao de teclas (quando a tecla eh apertada e segurada)
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            
            case SDL_QUIT:
                quitRequested = true;
                break;
        }
    }
}

bool InputManager::KeyPress (int key) {
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease (int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown (int key) {
    return keyState[key];
}

bool InputManager::MousePress (int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease (int button) {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown (int button) {
    return mouseState[button];
}

int InputManager::GetMouseX () {
    return mouseX;
}

int InputManager::GetMouseY () {
    return mouseY;
}

bool InputManager::QuitRequested () {
    return quitRequested;
}

InputManager& InputManager::GetInstance () {
    static InputManager im;
    return im;
}

InputManager::InputManager () {
    updateCounter = 0;
    quitRequested = false;
}

InputManager::InputManager (const InputManager& im) {

}

InputManager& InputManager::operator= (const InputManager& im) {
    
}

InputManager::~InputManager () {

}
#pragma GCC diagnostic pop
