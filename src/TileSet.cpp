#include "TileSet.h"

#define TILESETFILE "assets/img/tileset.png"

using std::shared_ptr;

shared_ptr<GameObject> go = shared_ptr<GameObject> (new GameObject());

TileSet::TileSet(int tileWidth, int tileHeight, string file) :  tileSet(*go, TILESETFILE),
                                                                tileWidth(tileWidth),
                                                                tileHeight(tileHeight){

    rows = tileSet.GetHeight()/tileHeight;
    columns = tileSet.GetWidth()/tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y){

    if(index < (unsigned)rows * columns){
        tileSet.SetClip(GetTileWidth() * (index%columns), GetTileHeight() * (index/columns), GetTileWidth(), GetTileHeight());
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth(){

    return tileWidth;
}

int TileSet::GetTileHeight(){

    return tileHeight;
}