#ifndef TILESET_HPP
#define TILESET_HPP

class TileSet;

#include <string>

#include "Sprite.hpp"

class TileSet {
  public:
    TileSet( unsigned int tileWidth, unsigned int tileHeight, std::string file );

    void Render( unsigned int index, float x, float y );
    unsigned int GetTileWidth();
    unsigned int GetTileHeight();
    
  private:
    Sprite tileSet;
    unsigned int rows;
    unsigned int columns;
    unsigned int tileWidth;
    unsigned int tileHeight;
};

#endif // TILESET_HPP
