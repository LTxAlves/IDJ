#include <fstream>
#include "TileMap.h"

using std::ifstream;

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated){

    Load(file);
    this->tileSet = tileSet;
}

void TileMap::Load(string file){

    ifstream inFile;
    inFile.open(file.c_str());

    if(!inFile){
        SDL_Log("Unable to Load file %s:", file.c_str());
        exit(1);
    }

    inFile.close();
}

void TileMap::SetTileSet(TileSet* tileSet){

}

int& TileMap::At(int x, int y, int z = 0){


}

void TileMap::Render(){

}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0){

}

int TileMap::GetWidth(){

    return mapWidht;
}

int TileMap::GetHeight(){

    return mapHeight;
}

int TileMap::GetDepth(){
    
    return mapDepth;
}