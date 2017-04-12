# IDJ Tutorial Game
#### O jogo tutorial da matéria de Introdução ao Desenvolvimento de Jogos 1/2017 - UnB

Todo o código está sendo testado no Windows 10 64-bit e no Linux Mint Cinnamon 18.1.

## Dependências
- Mingw64 (Windows) / g++, makefile (Linux)
- SDL2
    - SDL2_image
    - SDL2_mixer
    - SDL2_ttf
    - ~~SDL2_net~~

## Instruções de instalação
###### Somente prossiga se as dependências estiverem corretamente instalados e funcionando!
- Baixe esse repositório
- Vá até o diretório raiz do projeto com um terminal
- Execute `make` (Linux) / `mingw32-make` (Windows)
- Copie todo o conteúdo da pasta `.\resources ` para dentro de `.\build`
- Se você estiver no Windows, copie todo o conteúdo de `.\win-DLLs` para a pasta `.\build`

*OBS.: O arquivo copy.bat funciona temporariamente __somente para Windows__. Ele automatiza as duas últimas etapas. Para isso, basta executar `.\copy.bat release`.*