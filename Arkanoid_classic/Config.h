
#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <iostream>
#include <list>
#include <random>				//Для задания случайного направления полета шарика при первом его запуске с платформы
#include <sstream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>



using namespace sf;

const std::string IMGPATH = "Images/Sprites_Arkanoid.png";
const std::string FONTPATH = "Fonts/Neucha/Neucha-Regular.ttf";
const std::string MUSIC_BASE = "MusicAndSounds/Stupid_Dancer.wav";
const std::string SOUND_BALL_BOUNCE_OFF_BLOCK = "MusicAndSounds/ballBounceOfBlock.wav";
const std::string SOUND_BALL_BOUNCE_OFF_BORDER_MAP = "MusicAndSounds/ballBounceOfBorderMap.wav";
const std::string SOUND_BALL_BOUNCE_OFF_PLATFORM = "MusicAndSounds/ballBounceOfPlatform.wav";
const std::string SOUND_BALL_FALL = "MusicAndSounds/ballFall.wav";
const std::string SOUND_BULLET_HIT_BLOCK = "MusicAndSounds/bulletHitBlock.wav";
const std::string SOUND_BULLET_HIT_BORDER_MAP = "MusicAndSounds/bulletHitBorderMap.wav";
const std::string SOUND_PLATFORM_COLLECTS_BONUS = "MusicAndSounds/platformCollBonus.wav";
const std::string SOUND_PLATFORM_FIRE = "MusicAndSounds/platformFire.wav";
const std::string SOUND_BALL_START = "MusicAndSounds/ballStart.wav";
const std::string SOUND_BALL_CATCH = "MusicAndSounds/ballCatch.wav";
const std::string SOUND_CHANGE_PLATFORM = "MusicAndSounds/changePlatform.wav";




// Границы меню
const int BORDER_RIGHT = 775;
const int BORDER_LEFT = 25;
const int BORDER_TOP = 23;
const int BORDER_BOTTOM = 600;



//------------------------------------------Элементы спрайтов

//------------------------------------------------Платформа

// Большая платформа
const int LARGE_PLATFORM_LEFT = 148;
const int LARGE_PLATFORM_TOP = 302;
const int LARGE_PLATFORM_WIDTH = 128;
const int LARGE_PLATFORM_HEIGHT = 31;

// Средняя платформа
const int MEDIUM_PLATFORM_LEFT = 58;
const int MEDIUM_PLATFORM_TOP = 302;
const int MEDIUM_PLATFORM_WIDTH = 90;
const int MEDIUM_PLATFORM_HEIGHT = 31;

// Маленькая платформа
const int SMALL_PLATFORM_LEFT = 0;
const int SMALL_PLATFORM_TOP = 302;
const int SMALL_PLATFORM_WIDTH = 58;
const int SMALL_PLATFORM_HEIGHT = 31;

//-------------------------------------------------------------------Шарик
// Шарик
const int BLUE_BALL_LEFT = 64;
const int BLUE_BALL_TOP = 128;
const int BLUE_BALL_WIDTH = 16;
const int BLUE_BALL_HEIGHT = 16;


//--------------------------------------------------------------------Блоки
const int BLOCK_WIDTH = 54;
const int BLOCK_HEIGHT = 22;

// Желтый блок
const int YELLOW_BLOCK_LEFT = 648;
const int YELLOW_BLOCK_TOP = 22;

// Бонусный желтый блок
const int YELLOW_BONUS_BLOCK_LEFT = 594;
const int YELLOW_BONUS_BLOCK_TOP = 374;

// Зеленый блок
const int GREEN_BLOCK_LEFT = 378;
const int GREEN_BLOCK_TOP = 22;

// Бонусный зеленый блок
const int GREEN_BONUS_BLOCK_LEFT = 648;
const int GREEN_BONUS_BLOCK_TOP = 308;

// Розовый блок
const int PINK_BLOCK_LEFT = 486;
const int PINK_BLOCK_TOP = 22;

//Бонусный розовый блок
const int PINK_BONUS_BLOCK_LEFT = 648;
const int PINK_BONUS_BLOCK_TOP = 330;

// Фиолетовый блок
const int PURPLE_BLOCK_LEFT = 540;
const int PURPLE_BLOCK_TOP = 22;

// Бонусный фиолетовый блок
const int PURPLE_BONUS_BLOCK_LEFT = 594;
const int PURPLE_BONUS_BLOCK_TOP = 352;

//Красный блок
const int RED_BLOCK_LEFT = 594;
const int RED_BLOCK_TOP = 22;

// Бонусный красный блок
const int RED_BONUS_BLOCK_LEFT = 648;
const int RED_BONUS_BLOCK_TOP = 352;

// Голубой блок
const int BLUE_BLOCK_LEFT = 324;
const int BLUE_BLOCK_TOP = 22;

// Бонусный голубой блок
const int BLUE_BONUS_BLOCK_LEFT = 594;
const int BLUE_BONUS_BLOCK_TOP = 308;

// Оранженвый блок
const int ORANGE_BLOCK_LEFT = 432;
const int ORANGE_BLOCK_TOP = 22;

//----------------------------------------------------------------------------Бонусы
const int BONUS_WIDTH = 27;
const int BONUS_HEIGHT = 30;

// Голубой бонус
const int BLUE_BONUS_LEFT = 456;
const int BLUE_BONUS_TOP = 449;

// Зеленый бонус
const int GREEN_BONUS_LEFT = 488;
const int GREEN_BONUS_TOP = 449;

// Розовый бонус
const int PINK_BONUS_LEFT = 520;
const int PINK_BONUS_TOP = 449;

// Фиолетовый бонус
const int PURPLE_BONUS_LEFT = 553;
const int PURPLE_BONUS_TOP = 449;

// Красный бонус
const int RED_BONUS_LEFT = 456;
const int RED_BONUS_TOP = 482;

// Желтый бонус
const int YELLOW_BONUS_LEFT = 488;
const int YELLOW_BONUS_TOP = 481;

//--------------------------------------------------------------------------------Пули

const int BULLET_LEFT = 225;
const int BULLET_TOP = 6;
const int BULLET_WIDTH = 12;
const int BULLET_HEIGHT = 12;

//-------------------------------------------------------------------------------Спрайты границ

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
//-----------------------------------------------------------------------------Конец элементов спрайтов


//-----------------------------------------------------------------------------Границы карты и меню


// Количество тайликов для прорисовки карты 
// Границы карты
const int WIDTH_MAP = 25;
const int HEIGHT_MAP = 22;
// Границы меню
const int WIDTH_MENU = 34;
const int HEIGHT_MENU = 20;


//------------------------------------------------------------------------------Стартовые позиции

//платформа
const sf::Vector2f PLATFORM_START_POSITION = Vector2f(320.f, 550.f);

//Шарик стартовая позиция
const sf::Vector2f BALL_START_POSITION = Vector2f(376.f, 534.f);
//Шарик относительно платформы
const sf::Vector2f BALL_RELATIVE_PLATFORM = Vector2f(56.f, -16.f);

enum sizePlatform {smallPlatform = 1, mediumPlatform = 2, largePlatform = 3};


//----------------------------------------------------------------------------------Цветка Бонусов и Блков 

enum BlockType { NO_BONUS, BLUE, GREEN, ORANGE, PINK, PURPLE, RED, YELLOW };
/*
* Blue	  - увеличивает / уменьшает платформу
* Green	  - шарик прилипает к платформе
* Orange  - не имеет бонуса
* Pink	  - из одного шарика становится три 
* Purple  - замедляет / ускоряет платформу
* Red     - платформа стреляет плуями по блокам
* Yellow  - игроку добавляется одна жизнь
*/
#endif