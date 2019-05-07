#pragma once

#include <iostream>
using std::string;

/*Math constants*/
const float PI = 3.14159265359; //value of constant pi
/***************************************************************************************/

/*Screen size*/
const int SCREEN_HEIGHT = 600; //constant for screen height
const int SCREEN_WIDTH  = 1024; //constant for screen width
/***************************************************************************************/

/*Tiles sizes*/
const int TILEWIDTH     = 64; //tile width in pixels
const int TILEHEIGHT    = 64; //tile height in pixels
/***************************************************************************************/

/*File locations*/
const string ALIENFILE          = "assets/img/alien.png"; //alien image file
const string MINIONFILE         = "assets/img/minion.png"; //minion image file

const string MINIONBULLET1FILE  = "assets/img/minionbullet1.png"; //minion bullet 1 file
const string MINIONBULLET2FILE  = "assets/img/minionbullet2.png"; //minion bullet 2 file

const string BGIMAGEFILE        = "assets/img/ocean.jpg"; //background image file
const string MUSICFILE          = "assets/audio/stageState.ogg"; //background music file

const string TILESETFILE        = "assets/img/tileset.png"; //tileset file
const string TILEMAPFILE        = "assets/map/tileMap.txt"; //tilemap file

const string BOOMAUDIOFILE      = "assets/audio/boom.wav"; //explosion audio file

const string PENGUINFACEFILE    = "assets/img/penguinface.png"; //penguin face file
const string PENGUINBODYFILE    = "assets/img/penguin.png"; //penguin body file
const string PENGUINCANNONFILE  = "assets/img/cubngun.png"; //penguin cannon file 
/***************************************************************************************/


/*Speed and Movement*/
const int ALIENSPEED        = 150; //default speed for alien
const int CAMERA_SPEED      = 300; //default speedfor camera

const float MINIONANGVEL    = 30.0 * PI/180; //default angular velocity for minion translation
const float ALIENANGVEL     = 20.0 * PI/180; //default alien angular velocity
const float BULLETSPEED     = 500; //default speed for bullet
const float BULLETMAXDIST   = 1500; //default distance bullet can move
const float PARALLAX_FACTOR = 1.5; //relative movement factor between layers
/***************************************************************************************/

/*Number of instances*/
const int NMINIONSSTD   = 4; //standard number of minons
const int BULLETFRAMES  = 3; //number of frames in bullet image 
/***************************************************************************************/

/*Frame durations*/
const float BULLETFRAMETIME = 0.5;
/***************************************************************************************/