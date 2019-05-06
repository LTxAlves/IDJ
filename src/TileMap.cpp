#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"

int error = -2; //default error for reference only

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated){

    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(string file){

    ifstream inFile;
    inFile.open(file.c_str());

    if(!inFile){ //Checks if file was opened/if it exists
        SDL_Log("Unable to Load file %s:", file.c_str());
        exit(1);
    }

    string line;
    stringstream ss;
    vector<int> numbers;
    int intNum;
    string trash;

    while(getline(inFile, line, ',')){ //reads line ignoring ',' character
        line.erase(remove(line.begin(), line.end(), '\r'), line.end()); //removes carriage return (used in Windows based OS for end of line) if it exists
        line.erase(remove(line.begin(), line.end(), '\n'), line.end()); //removes end of line character if it exists
        line.erase(remove(line.begin(), line.end(), '\0'), line.end()); //end empty character if it exists
        ss.str(line);

        if(ss >> intNum)
            numbers.push_back(intNum);

        ss.clear();
    }

    inFile.close();

    if(numbers.size() < 3){ //file should have values for width, height and depth of map
        SDL_Log("Error! File \"%s\" does not contain information for width, height and depth of map.\n", file.c_str());
        exit(1);
    }

    mapWidth = numbers[0];
    mapHeight = numbers[1];
    mapDepth = numbers[2];

    if(mapWidth <= 0 || mapHeight <= 0 || mapDepth <= 0){ //validades values
        SDL_Log("Invalid value for map width, height or depth!\n");
        exit(1);
    }

    int tiles = mapWidth * mapHeight * mapDepth; //number of tiles that should exist

    if((int) numbers.size() - 3 != tiles){ //checks if map file contains the correct number of tiles
        SDL_Log("Incorrect tile mapping!\nNumber of tiles doesn't match with width, height and depth specification!\n");
        exit(1);
    }

    for(int i = 0; i < tiles; i++) //saves tiles after validation
        tileMatrix.push_back(numbers[i+3] - 1);
}

void TileMap::SetTileSet(TileSet* tileSet){

    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z = 0){

    int position = 0;

    if(x < 0 || x >= mapWidth){ //data validation
        SDL_Log("x = %d not within range of 0 <= x < mapWidth!\n", x);
        return error;
    }

    if(y < 0 || y >= mapHeight){ //data validation
        SDL_Log("y = %d not within range of 0 <= y < mapHeight!\n", y);
        return error;
    }
    
    if(z < 0 || z >= mapDepth){ //data validation
        SDL_Log("z = %d not within range of 0 <= z < mapDepth!\n", z);
        return error;
    }

    position += z * mapWidth * mapHeight; //z coordinate (moves acoording to width and height)
    position += y * mapWidth; //y coordinate (moves according to width)
    position += x; //x coordinate

    return tileMatrix[position];
}

void TileMap::Render(){

    for(int i = 0; i < mapDepth; i++)
        RenderLayer(i, Camera::pos.x * (1 + i * PARALLAX_FACTOR), Camera::pos.y * (1 + i * PARALLAX_FACTOR));
}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0){

    int width, height;

	for(int j = 0; j < GetHeight(); j++){
		for(int i = 0; i < GetWidth(); i++){
            width = i * tileSet->GetTileWidth();
            height = j * tileSet->GetTileHeight();
			tileSet->RenderTile(At(i, j, layer), cameraX + width, cameraY + height);
		}
	}
}

int TileMap::GetWidth(){

    return mapWidth;
}

int TileMap::GetHeight(){

    return mapHeight;
}

int TileMap::GetDepth(){
    
    return mapDepth;
}

bool TileMap::Is(string type){

    return !type.compare("TileMap");    
}

void TileMap::Update(float dt){

    //does nothing
}