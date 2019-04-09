#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <iostream>
#include <vector>
#include "TileSet.h"
#include "Component.h"

using std::vector;
using std::string;

class TileMap : public Component{

    public:
        TileMap(GameObject&, string, TileSet*);

        void Load(string);

        void SetTileSet(TileSet*);

        int& At(int, int, int);

        void Render();

        void RenderLayer(int ,int, int);

        int GetWidth();
        int GetHeight();
        int GetDepth();

    private:
        vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidht, mapHeight, mapDepth;
};

#endif //TILE_MAP_H