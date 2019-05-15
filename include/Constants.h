#pragma once

#include <iostream>
using std::string;

/*Math constants*/
const float PI          = 3.14159265359; //value of constant pi
const float RADTODEG    = 180/PI; //value to get radians from degrees
const float DEGTORAD    = PI/180; //value to get degrees from radians
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
const string ALIENDEATHFILE     = "assets/img/aliendeath.png";
const string MINIONFILE         = "assets/img/minion.png"; //minion image file
const string MINIONBULLET1FILE  = "assets/img/minionbullet1.png"; //minion bullet 1 file
const string MINIONBULLET2FILE  = "assets/img/minionbullet2.png"; //minion bullet 2 file
const string MINIONDEATHFILE    = "assets/img/miniondeath.png";

const string BGIMAGEFILE        = "assets/img/ocean.jpg"; //background image file
const string MUSICFILE          = "assets/audio/stageState.ogg"; //background music file

const string TILESETFILE        = "assets/img/tileset.png"; //tileset file
const string TILEMAPFILE        = "assets/map/tileMap.txt"; //tilemap file

const string BOOMAUDIOFILE      = "assets/audio/boom.wav"; //explosion audio file

const string PENGUINFACEFILE    = "assets/img/penguinface.png"; //penguin face file
const string PENGUINBODYFILE    = "assets/img/penguin.png"; //penguin body file
const string PENGUINCANNONFILE  = "assets/img/cubngun.png"; //penguin cannon file
const string PENGUINBULLETFILE  = "assets/img/penguinbullet.png"; //penguin bullets file
const string PENGUINDEATHFILE   = "assets/img/penguindeath.png"; //penguin death sprite sheet file
/***************************************************************************************/


/*Speed and Movement*/
const int   ALIENSPEED      = 150; //default speed for alien
const int   CAMERA_SPEED    = 300; //default speedfor camera

const int   PLAYERSPEEDCAP  = 200; //maximum linear speed for player's pengiun
const int   PLAYERACCEL     = 300; //player's penguin's linear acceleration
const float PLAYERANGVEL    = 50.0 * DEGTORAD; //player's pengiun's angular velocity

const float MINIONANGVEL    = 30.0 * DEGTORAD; //default angular velocity for minion translation
const float ALIENANGVEL     = 20.0 * DEGTORAD; //default alien angular velocity

const float BULLETSPEED     = 500; //default speed for bullet
const float BULLETMAXDIST   = 1500; //default distance bullet can move

const float PARALLAX_FACTOR = 1.5; //relative movement factor between layers
/***************************************************************************************/

/*Number of instances*/
const int NMINIONSSTD           = 4; //standard number of minons
const int MINIONBULLETFRAMES    = 3; //number of frames in minion bullet image

const int ENEMYDEATHFRAMES      = 4; //number of frames in alien and minion death images

const int PENGUINDEATHFRAMES    = 5; //number of frames in penguin death image

const int PENGUINBULLETFRAMES   = 4; //number of frames in penguin bullet image
/***************************************************************************************/

/*Frame durations*/
const float MINIONBULLETFRAMETIME   = 0.1; //frame duration for minion's bullets
const float PENGUINBULLETFRAMETIME  = 0.5; //frame duration for penguin's bullets

const float DEATHFRAMETIME          = 0.15; //frame duration for deaths
/***************************************************************************************/

/*Timer values*/
const float PENGUINSHOTCOOLDOWN = 0.6;

const float ALIENRESTCOOLDOWN   = 0.9;
/***************************************************************************************/