# IDJ Tutorial Game
#### O jogo tutorial da matéria de Introdução ao Desenvolvimento de Jogos 1/2017 - UnB

Todo o código está sendo testado no Windows 10 64-bit e no Linux Mint Cinnamon 18.1.

## Dependências
- Mingw64 (Windows) / g++, makefile (Linux)
- CMake
- SDL2
    - SDL2_image
    - SDL2_mixer
    - SDL2_ttf
    - ~~SDL2_net~~

## Instruções de instalação
###### Somente prossiga se as dependências estiverem corretamente instalados e funcionando!
- ### Windows
    - Baixe esse repositório
    - Aqui existem três possibilidades:
        - Procedimento 1 (válido somente se você usa o MinGW):
            1. Vá até o diretório raiz do projeto com um prompt de comando
            2. Execute o `build.bat`
        - Procedimento 2:
            1. Vá até o diretório build do projeto com um prompt de comando
            2. Execute `cmake ..`
            3. Execute `make`
        - Procedimento 3:
            1. Abra o CMake GUI
            2. Selecione a pasta raiz do projeto como a que possui o código fonte
            3. Selecione a pasta build (ou qualquer subpasta dela que desejar) como local para fazer o build
            4. Configure e gere
            5. Execute make gerado na pasta de destino escolhida
    - Se você seguiu o procedimento 1, acaba por aqui. O executável está na pasta `build/<Debug;Release>`.
    - Se você seguiu o procedimento 2 ou 3, copie o conteúdo da pasta win-DLLs e cole no mesmo local que o executável foi gerado.
- ### Linux
    - Baixe esse repositório
    - Vá até o diretório build do projeto com um terminal
    - Execute `cmake ..`
    - Execute `make`