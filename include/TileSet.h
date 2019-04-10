#ifndef TILE_SET_H
#define TILE_SET_H

#include <iostream>
#include "GameObject.h"
#include "Sprite.h"

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

#endif //TILE_SET_H