#include "TileMap.hpp"

TileMap::TileMap (std::string file, TileSet* tileSet) {
    Load (file);
    this->tileSet = tileSet;
}

void TileMap::Load (std::string file) {
    std::fstream fs (file, std::fstream::in);

    fs >> mapWidth;
    fs.ignore(1);
    fs >> mapHeight;
    fs.ignore(1);
    fs >> mapDepth;
    fs.ignore(1);

    tileMatrix = std::vector<int>(mapDepth*mapHeight*mapWidth);

    int elem;
    for (int i = 0; i < mapDepth*mapHeight*mapWidth; ++i) {
        fs >> elem;
        fs.ignore(1);
        tileMatrix[i] = elem-1;
    }
    
    fs.close ();
}

void TileMap::SetTileSet (TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At (int x, int y, int z) {
    return *((int*)(tileMatrix.data()) + x + mapWidth*y + mapWidth*mapHeight*z);
}

void TileMap::Render (int cameraX, int cameraY) {
    for (int i = 0; i < mapDepth; ++i) {
        RenderLayer (i, cameraX, cameraY);
    }
}

void TileMap::RenderLayer (int layer, int cameraX, int cameraY) {
    int dx = tileSet->GetTileWidth ();
    int dy = tileSet->GetTileHeight ();
    for (int j = 0; j < mapHeight; ++j) {
        for (int i = 0; i < mapWidth; i++) {
            int index = At(i,j,layer);
            if (index > -1) {
                tileSet->Render (index, i*dx-cameraX, j*dy-cameraY);
            }
        }
    }
}

int TileMap::GetWidth () {
    return mapWidth;
}

int TileMap::GetHeight () {
    return mapHeight;
}

int TileMap::GetDepth () {
    return mapDepth;
}