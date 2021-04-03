
#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <random>				
#include <sstream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>



using namespace sf;
using std::string;

const string IMGPATH = "Images/Sprites_Arkanoid.png";
const string FONTPATH = "Fonts/Neucha/Neucha-Regular.ttf";
const string LEVEL_CREATOR_PATH = "Config/lvlCreator.ini";
const string MUSIC_BASE = "MusicAndSounds/Stupid_Dancer.wav";
const string SOUND_BALL_BOUNCE_OFF_BLOCK = "MusicAndSounds/ballBounceOfBlock.wav";
const string SOUND_BALL_BOUNCE_OFF_BORDER_MAP = "MusicAndSounds/ballBounceOfBorderMap.wav";
const string SOUND_BALL_BOUNCE_OFF_PLATFORM = "MusicAndSounds/ballBounceOfPlatform.wav";
const string SOUND_BALL_FALL = "MusicAndSounds/ballFall.wav";
const string SOUND_BULLET_HIT_BLOCK = "MusicAndSounds/bulletHitBlock.wav";
const string SOUND_BULLET_HIT_BORDER_MAP = "MusicAndSounds/bulletHitBorderMap.wav";
const string SOUND_PLATFORM_COLLECTS_BONUS = "MusicAndSounds/platformCollBonus.wav";
const string SOUND_PLATFORM_FIRE = "MusicAndSounds/platformFire.wav";
const string SOUND_BALL_START = "MusicAndSounds/ballStart.wav";
const string SOUND_BALL_CATCH = "MusicAndSounds/ballCatch.wav";
const string SOUND_CHANGE_PLATFORM = "MusicAndSounds/changePlatform.wav";




// Border menu
const int BORDER_RIGHT = 775;
const int BORDER_LEFT = 25;
const int BORDER_TOP = 23;
const int BORDER_BOTTOM = 600;



//------------------------------------------sprites Elemtnts

//------------------------------------------------Platform

// Large platform
const int LARGE_PLATFORM_LEFT = 148;
const int LARGE_PLATFORM_TOP = 302;
const int LARGE_PLATFORM_WIDTH = 128;
const int LARGE_PLATFORM_HEIGHT = 31;

// Middle platform
const int MEDIUM_PLATFORM_LEFT = 58;
const int MEDIUM_PLATFORM_TOP = 302;
const int MEDIUM_PLATFORM_WIDTH = 90;
const int MEDIUM_PLATFORM_HEIGHT = 31;

// Small platform
const int SMALL_PLATFORM_LEFT = 0;
const int SMALL_PLATFORM_TOP = 302;
const int SMALL_PLATFORM_WIDTH = 58;
const int SMALL_PLATFORM_HEIGHT = 31;

//-------------------------------------------------------------------Ball
// Ball
const int BLUE_BALL_LEFT = 64;
const int BLUE_BALL_TOP = 128;
const int BLUE_BALL_WIDTH = 16;
const int BLUE_BALL_HEIGHT = 16;


//-------------------------------------------------------------------Blocks
const int BLOCK_WIDTH = 54;
const int BLOCK_HEIGHT = 22;

// Yellow block
const int YELLOW_BLOCK_LEFT = 648;
const int YELLOW_BLOCK_TOP = 22;

// Bonus Yellow block
const int YELLOW_BONUS_BLOCK_LEFT = 594;
const int YELLOW_BONUS_BLOCK_TOP = 374;

// Green block
const int GREEN_BLOCK_LEFT = 378;
const int GREEN_BLOCK_TOP = 22;

// Bonus Green block
const int GREEN_BONUS_BLOCK_LEFT = 648;
const int GREEN_BONUS_BLOCK_TOP = 308;

// Pink block
const int PINK_BLOCK_LEFT = 486;
const int PINK_BLOCK_TOP = 22;

// Bonus pink block
const int PINK_BONUS_BLOCK_LEFT = 648;
const int PINK_BONUS_BLOCK_TOP = 330;

// Purple block
const int PURPLE_BLOCK_LEFT = 540;
const int PURPLE_BLOCK_TOP = 22;

// Bonus purple block
const int PURPLE_BONUS_BLOCK_LEFT = 594;
const int PURPLE_BONUS_BLOCK_TOP = 352;

// Red block
const int RED_BLOCK_LEFT = 594;
const int RED_BLOCK_TOP = 22;

// Bonus red block
const int RED_BONUS_BLOCK_LEFT = 648;
const int RED_BONUS_BLOCK_TOP = 352;

// Blue block
const int BLUE_BLOCK_LEFT = 324;
const int BLUE_BLOCK_TOP = 22;

// Bonus blue block
const int BLUE_BONUS_BLOCK_LEFT = 594;
const int BLUE_BONUS_BLOCK_TOP = 308;

// Orange block
const int ORANGE_BLOCK_LEFT = 432;
const int ORANGE_BLOCK_TOP = 22;

//---------------------------------------------------------------------------Bonuses
const int BONUS_WIDTH = 27;
const int BONUS_HEIGHT = 30;

// Blue bonus
const int BLUE_BONUS_LEFT = 456;
const int BLUE_BONUS_TOP = 449;

// Green bonus
const int GREEN_BONUS_LEFT = 488;
const int GREEN_BONUS_TOP = 449;

// Pink bonus
const int PINK_BONUS_LEFT = 520;
const int PINK_BONUS_TOP = 449;

// Purple bonus
const int PURPLE_BONUS_LEFT = 553;
const int PURPLE_BONUS_TOP = 449;

// Red bonus
const int RED_BONUS_LEFT = 456;
const int RED_BONUS_TOP = 482;

// Yellow bonus
const int YELLOW_BONUS_LEFT = 488;
const int YELLOW_BONUS_TOP = 481;

//--------------------------------------------------------------------------------Bulelts

const int BULLET_LEFT = 225;
const int BULLET_TOP = 6;
const int BULLET_WIDTH = 12;
const int BULLET_HEIGHT = 12;

//-------------------------------------------------------------------------------Border Sprites

const int CORNER_WIDTH = 32;
const int CORNER_HEIGHT = 32;
const int CORNER_LEFT = 0;
const int CORNER_TOP = 2;
const int CORNER_RIGHT = 32;
const int CORNER_BOTTOM = 32;

const int VERTICAL_WALL_WIDTH = 31;
const int VERTICAL_WALL_HEIGHT = 30;
const int VERTICAL_WALL_LEFT = 64;
const int VERTICAL_WALL_TOP = 0;
const int VERTICAL_WALL_RIGHT = 96;

const int HORIZONTAL_WALL_WIDTH = 32;
const int HORIZONTAL_WALL_HEIGHT = 32;
const int HORIZONTAL_WALL_LEFT = 64;
const int HORIZONTAL_WALL_TOP = 32;
const int HORIZONTAL_WALL_BOTTOM = 62;
//-----------------------------------------------------------------------------Elements sprites end


//-----------------------------------------------------------------------------Border map and menu


// Counters tiles for map
// Border map
const int WIDTH_MAP = 25;
const int HEIGHT_MAP = 22;
// Border menu
const int WIDTH_MENU = 34;
const int HEIGHT_MENU = 20;


//------------------------------------------------------------------------------start positions

// Platform 
const sf::Vector2f PLATFORM_START_POSITION = Vector2f(320.f, 550.f);

// Ball
const sf::Vector2f BALL_START_POSITION = Vector2f(376.f, 534.f);
const sf::Vector2f BALL_RELATIVE_PLATFORM = Vector2f(56.f, -16.f);

enum sizePlatform {smallPlatform = 1, mediumPlatform = 2, largePlatform = 3};

//----------------------------------------------------------------------------------Bonuses and blocks color 

enum BlockType { NO_BONUS, BLUE, GREEN, ORANGE, PINK, PURPLE, RED, YELLOW };
/*
* Blue	  - Uvelichivaet / umenshaen platformu
* Green	  - ball catch to the platform
* Orange  - don't have a bonus
* Pink	  - ball * 3 
* Purple  - slow or fast ball
* Red     - add bullets
* Yellow  - additional lives
*/

//------------------------------------------------------------------------------------default ball speed
const float DEFAULT_BALL_SPEED = 0.3;
const float MAX_BALL_SPEED = 0.8;
#endif