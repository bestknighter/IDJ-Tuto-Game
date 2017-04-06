#ifndef _TILESET_HPP_
#define _TILESET_HPP_

class TileSet;

#include <string>

#include "Sprite.hpp"

class TileSet {
  public:
    TileSet (int tileWidth, int tileHeight, std::string file);
    void Render (unsigned int index, float x, float y);
    int GetTileWidth ();
    int GetTileHeight ();
  private:
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
};

#endif //_TILESET_HPP_