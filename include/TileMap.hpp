#ifndef _TILEMAP_HPP_
#define _TILEMAP_HPP_

class TileMap;

#include <string>
#include <vector>
#include <fstream>

#include "TileSet.hpp"

class TileMap {
  public:
    TileMap (std::string file, TileSet* tileSet);
    void Load (std::string file); // Carrega arquivo com os indices do mapa
    void SetTileSet (TileSet* tileSet); // Seta "a skin" do mapa
    int& At (int x, int y, int z = 0); // Retorna o indice de tile a ser usado naquela coordenada
    // Renderiza todas as layers entre firstLayer (inclusivo) e lastLayer (inclusivo, -1 para renderizar todas)
    void Render (int cameraX = 0, int cameraY = 0, unsigned int firstLayer = 0, unsigned int lastLayer = -1);
    void RenderLayer (unsigned int layer, int cameraX = 0, int cameraY = 0); // Renderiza uma layer em especifico
    unsigned int GetWidth ();
    unsigned int GetHeight ();
    unsigned int GetDepth ();
  private:
    std::vector<int> tileMatrix; // Vetor com todos os indices do mapa
    TileSet* tileSet; // "Skin" do mapa
    unsigned int mapWidth;
    unsigned int mapHeight;
    unsigned int mapDepth;
};

#endif // _TILEMAP_HPP_
