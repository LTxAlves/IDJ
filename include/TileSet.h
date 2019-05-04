#pragma once

#include <iostream>
#include "GameObject.h"
#include "Sprite.h"

#define TILESETFILE "assets/img/tileset.png"

using std::shared_ptr;
using std::string;

class TileSet{
    public:
        TileSet(int, int, string);

        void RenderTile(unsigned int, float, float);

        int GetTileHeight();
        int GetTileWidth();

    private:
        Sprite tileSet;

        int rows, columns;

        int tileWidth, tileHeight;
};