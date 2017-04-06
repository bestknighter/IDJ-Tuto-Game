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
    void Load (std::string file);
    void SetTileSet (TileSet* tileSet);
    int& At (int x, int y, int z = 0);
    void Render (int cameraX = 0, int cameraY = 0);
    void RenderLayer (int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth ();
    int GetHeight ();
    int GetDepth ();
  private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif //_TILEMAP_HPP_