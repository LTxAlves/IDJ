#include "TileSet.h"

using std::unique_ptr;

unique_ptr<GameObject> GO = unique_ptr<GameObject> (new GameObject());

TileSet::TileSet(int tileWidth, int tileHeight, string file) :  tileSet(*GO, "assets/img/tileset.png"),
                                                                tileWidth(tileWidth),
                                                                tileHeight(tileHeight){

    rows = tileSet.GetHeight()/tileHeight;
    columns = tileSet.GetWidth()/tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y){

    if(index <= (unsigned)rows*columns){
        tileSet.SetClip(0, 0, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth(){

    return tileWidth;
}

int TileSet::GetTileHeight(){

    return tileHeight;
}