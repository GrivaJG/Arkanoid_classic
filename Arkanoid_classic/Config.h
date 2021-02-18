#pragma once

#include <string>

const std::string IMGPATH = "Images/Sprites_Arkanoid.png";
const std::string FONTPATH = "Fonts/Neucha/Neucha-Regular.ttf";



// ������� ����
const int BORDER_RIGHT = 750;
const int BORDER_LEFT = 25;
const int BORDER_TOP = 25;
const int BORDER_BOTTOM = 700;



//------------------------------------------�������� ��������

//------------------------------------------------���������

// ������� ���������
const int LARGE_PLATFORM_LEFT = 148;
const int LARGE_PLATFORM_TOP = 302;
const int LARGE_PLATFORM_WIDTH = 128;
const int LARGE_PLATFORM_HEIGHT = 31;

// ������� ���������
const int MEDIUM_PLATFORM_LEFT = 58;
const int MEDIUM_PLATFORM_TOP = 302;
const int MEDIUM_PLATFORM_WIDTH = 90;
const int MEDIUM_PLATFORM_HEIGHT = 31;

// ��������� ���������
const int SMALL_PLATFORM_LEFT = 0;
const int SMALL_PLATFORM_TOP = 302;
const int SMALL_PLATFORM_WIDTH = 58;
const int SMALL_PLATFORM_HEIGHT = 31;

//-------------------------------------------------------------------�����
// �����
const int BLUE_BALL_LEFT = 64;
const int BLUE_BALL_TOP = 128;
const int BLUE_BALL_WIDTH = 16;
const int BLUE_BALL_HEIGHT = 16;


//--------------------------------------------------------------------�����
const int BLOCK_WIDTH = 54;
const int BLOCK_HEIGHT = 22;

// ������ ����
const int BLUE_BLOCK_LEFT = 648;
const int BLUE_BLOCK_TOP = 22;

// �������� ������ ����
const int BLUE_BONUS_BLOCK_LEFT = 594;
const int BLUE_BONUS_BLOCK_TOP = 374;

// ������� ����
const int GREEN_BLOCK_LEFT = 378;
const int GREEN_BLOCK_TOP = 22;

// �������� ������� ����
const int GREEN_BONUS_BLOCK_LEFT = 648;
const int GREEN_BONUS_BLOCK_TOP = 308;

// ������� ����
const int PINK_BLOCK_LEFT = 486;
const int PINK_BLOCK_TOP = 22;

//�������� ������� ����
const int PINK_BONUS_BLOCK_LEFT = 648;
const int PINK_BONUS_BLOCK_TOP = 330;

// ���������� ����
const int PURPLE_BLOCK_LEFT = 540;
const int PURPLE_BLOCK_TOP = 22;

// �������� ���������� ����
const int PURPLE_BONUS_BLOCK_LEFT = 594;
const int PURPLE_BONUS_BLOCK_TOP = 352;

//������� ����
const int RED_BLOCK_LEFT = 594;
const int RED_BLOCK_TOP = 22;

// �������� ������� ����
const int RED_BONUS_BLOCK_LEFT = 648;
const int RED_BONUS_BLOCK_TOP = 352;

// ������� ����
const int BLUE_BLOCK_LEFT = 324;
const int BLUE_BLOCK_TOP = 22;

// �������� ������� ����
const int BLUE_BONUS_BLOCK_LEFT = 594;
const int BLUE_BONUS_BLOCK_TOP = 308;

// ���������� ����
const int ORANGE_BLOCK_LEFT = 432;
const int ORANGE_BLOCK_TOP = 22;

//----------------------------------------------------------------------------������
const int BLUE_BONUS_WIDTH = 27;
const int BLUE_BONUS_HEIGHT = 30;

// ������� �����
const int BLUE_BONUS_LEFT = 456;
const int BLUE_BONUS_HEIGHT = 449;

// ������� �����
const int GREEN_BONUS_LEFT = 488;
const int GREEN_BONUS_HEIGHT = 449;

// ������� �����
const int PINK_BONUS_LEFT = 520;
const int PINK_BONUS_HEIGHT = 449;

// ���������� �����
const int PURPLE_BONUS_LEFT = 553;
const int PURPLE_BONUS_HEIGHT = 449;

// ������� �����
const int RED_BONUS_LEFT = 456;
const int RED_BONUS_HEIGHT = 482;

// ������ �����
const int YELLOW_BONUS_LEFT = 488;
const int YELLOW_BONUS_HEIGHT = 481;

//----------------------------------------------------------------------------������� ������

const int CORNER_WIDTH = 31;
const int CORNER_HEIGHT = 31;
const int CORNER_LEFT = 1;
const int CORNER_TOP = 2;
const int CORNER_RIGHT = 32;
const int CORNER_BOTTOM = 33;

const int WALL_WIDTH = 22;
const int WALL_HEIGHT = 22;
const int WALL_LEFT = 65;
const int WALL_TOP = 33;
//-----------------------------------------------------------------------------����� ��������� ��������


//-----------------------------------------------------------------------------������� ����� � ����


// ���������� �������� ��� ���������� ����� 
// ������� �����
const int WIDTH_MAP = 26;
const int HEIGHT_MAP = 22;
// ������� ����
const int WIDTH_MENU = 35;
const int HEIGHT_MENU = 20;


//------------------------------------------------------------------------------��������� �������

//���������
const sf::Vector2f PLATFORM_START_POSITION = Vector2f(320.f, 550.f);

//����� ��������� �������
const sf::Vector2f BALL_START_POSITION = Vector2f(376.f, 534.f);
//����� ������������ ���������
const sf::Vector2f BALL_RELATIVE_PLATFORM = Vector2f(56.f, -16.f);