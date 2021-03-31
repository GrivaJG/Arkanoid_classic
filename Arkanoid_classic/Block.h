#pragma once


#include "Config.h"
#include "GameObject.h"
#include "Ball.h"


class Block : public GameObject
{
private:
	
	

	int _strength = 0;    // ���������� ��������� � ���� �� ���������� 
	
	bool _flagBonus = false;  // ���� true �� ��� ��������� �� ����� �������� �����
	BlockType _blockType; // ���� ����� �������� �� ����������� �������� � ��� ������ ������� �� ��� ����� �������


	Vector2f BallCollisionLeftTopCorner(Ball& ball);		// ������������ � ����� ������� �����
	Vector2f BallCollisionRightTopCorner(Ball& ball);		// ������������ � ������ ������� �����
	Vector2f BallCollisionLeftBottomCorner(Ball& ball);	// ������������ � ����� ������ �����
	Vector2f BallCollisionRightBottomCorner(Ball& ball);	// ������������ � ������ ������ �����
	Vector2f BallCollisionLeftWall(Ball& ball);			// ������������ � ����� �������
	Vector2f BallCollisionBottomWall(Ball& ball);			// ������������ � �����
	Vector2f BallCollisionTopWall(Ball& ball);			// ������������ � ������
	Vector2f BallCollisionRightWall(Ball& ball);			// ������������ � ������ �������

public:
	Block(Image& img, BlockType blockType = NO_BONUS, bool bonus = false );
	~Block() { }


	Vector2f BallCollision(Ball& ball);

	BlockType GetBlockType() { return _blockType; }
	bool GetFlagBonus() { return _flagBonus; }	

};

