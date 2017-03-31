#include "TileSet.hpp"

TileSet::TileSet (int tileWidth, int tileHeight, std::string file) : tileSet (file.c_str ()) {
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    columns = tileSet.IsOpen () * (tileSet.GetWidth () / tileWidth);
    rows = tileSet.IsOpen () * (tileSet.GetHeight () / tileHeight);
}

void TileSet::Render (unsigned int index, float x, float y) {
    if (index < columns*rows) {
        int tileX = (index % columns) * tileWidth;
        int tileY = (index / columns) * tileHeight;
        tileSet.SetClip (tileX, tileY, tileWidth, tileHeight);
        tileSet.Render ((int)x, (int)y);
    }
}

int TileSet::GetTileWidth () {
    return tileWidth;
}

int TileSet::GetTileHeight () {
    return tileHeight;
}