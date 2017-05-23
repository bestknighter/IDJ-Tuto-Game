#include "TileMap.hpp"

TileMap::TileMap( std::string file, TileSet* tileSet ) {
    Load( file );
    this->tileSet = tileSet;
}

void TileMap::Load( std::string file ) {
    std::fstream fs ( file, std::fstream::in );

    // Le dimensoes ignorando o espaco em branco
    fs >> mapWidth;
    fs.ignore( 1 );
    fs >> mapHeight;
    fs.ignore( 1 );
    fs >> mapDepth;
    fs.ignore( 1 );

    tileMatrix = std::vector<int>( mapDepth * mapHeight * mapWidth );

    // Le os indices ignorando os espacos em branco
    int elem;
    for ( unsigned int i = 0; i < mapDepth * mapHeight * mapWidth; ++i ) {
        fs >> elem;
        fs.ignore( 1 );
        tileMatrix[i] = elem - 1;
    }
    
    fs.close();
}

void TileMap::SetTileSet( TileSet* tileSet ) {
    this->tileSet = tileSet;
}

int& TileMap::At( int x, int y, int z ) {
    return *( (int*)(tileMatrix.data()) + x + mapWidth * y + mapWidth * mapHeight * z );
}

void TileMap::Render( int cameraX, int cameraY, unsigned int firstLayer, unsigned int lastLayer ) {
    for ( int i = firstLayer; (i < (int)mapDepth) && (i <= (int)lastLayer); ++i ) {
        RenderLayer( i, cameraX * (i + 1), cameraY * (i + 1) );
    }
}

void TileMap::RenderLayer( unsigned int layer, int cameraX, int cameraY ) {
    int dx = tileSet->GetTileWidth();
    int dy = tileSet->GetTileHeight();
    // Percorre tile a tile do mapa e renderiza o tile de indice index naquela posicao
    for ( int j = 0; j < (int)mapHeight; ++j ) {
        for ( int i = 0; i < (int)mapWidth; ++i ) {
            int index = At( i, j, (int)layer );
            if ( index > -1 ) {
                tileSet->Render( index, i * dx - cameraX, j * dy - cameraY );
            }
        }
    }
}

unsigned int TileMap::GetWidth() {
    return mapWidth;
}

unsigned int TileMap::GetHeight() {
    return mapHeight;
}

unsigned int TileMap::GetDepth() {
    return mapDepth;
}
