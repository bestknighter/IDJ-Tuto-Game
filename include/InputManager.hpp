#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

class InputManager;

#define IMinstance InputManager::GetInstance ()

// Defines de teclado
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE

#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d

// Defines de mouse
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

#include <unordered_map>

#ifdef _WIN32
    #include "SDL_Events.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #include "SDL2/SDL_Events.h"
#elif __unix__
    #include "SDL2/SDL_Events.h"
#else
#   error "Unknown or unsupported compiler"
#endif

class InputManager {
  public:
    void Update (); // Atualiza estado do registros de estados
    // Teclado
    bool KeyPress (int key);
    bool KeyRelease (int key);
    bool IsKeyDown (int key);
    // Mouse
    bool MousePress (int button);
    bool MouseRelease (int button); 
    bool IsMouseDown (int button);

    int GetMouseX ();
    int GetMouseY ();

    // TRUE se houve clique para fechar a janela, ou ALT+F4 e similares, FALSE caso contrario
    bool QuitRequested ();

    static InputManager& GetInstance ();
  private:
    // Por ser singleton de Meyer, precisa esconder os seguintes
    InputManager (); // Constructor
    InputManager (const InputManager& im); // Copy Constructor
    InputManager& operator= (const InputManager& im); // Assignment Constructor
    ~InputManager (); // Destructor
    
    bool mouseState[6]; // Estado {CLICADO, NAO CLICADO} de cada botao do mouse
    int mouseUpdate[6]; // Quando houve a ultima atualizacao de estado de cada botao do mouse

    std::unordered_map<int, bool> keyState; // Estado {PRESSIONADO, NAO PRESSIONADO} de cada tecla do teclado
    std::unordered_map<int, int> keyUpdate; // Quando houve a ultima atualizacao de estado de cada tecla do teclado

    bool quitRequested;

    int updateCounter; // Conta qual frame esta

    // Posicao do Mouse
    int mouseX;
    int mouseY;
};

#endif // _INPUTMANAGER_HPP_
