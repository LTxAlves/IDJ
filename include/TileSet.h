#pragma once

#include <iostream>
#include <memory>
#include "Constants.h"
#include "Sprite.h"

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