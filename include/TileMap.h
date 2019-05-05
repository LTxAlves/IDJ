#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "TileSet.h"
#include "Component.h"

using std::vector;
using std::string;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::remove;

const float PARALLAX_FACTOR = 1.5;

class TileSet;

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

        bool Is(string);
        void Update(float);

    private:
        vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth, mapHeight, mapDepth;
};