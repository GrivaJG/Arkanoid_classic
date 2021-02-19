//#pragma once
//
//
//
//#include "GameObject.h"
//#include "Ball.h"
//
//
//class Block : public GameObject
//{
//private:
//	
//	std::list<Bonus*> bonus;
//
//	int _strength = 0;    // ���������� ��������� � ���� �� ���������� 
//	
//	bool _bonus = false;  // ���� true �� ��� ��������� �� ����� �������� �����
//	BlockType _blockType; // ���� ����� �������� �� ����������� ��������
//
//
//	Vector2f BallCollisionLeftTopCorner(Vector2f angleUnitCircle, Ball& ball);		// ������������ � ����� ������� �����
//	Vector2f BallCollisionRightTopCorner(Vector2f angleUnitCircle, Ball& ball);		// ������������ � ������ ������� �����
//	Vector2f BallCollisionLeftBottomCorner(Vector2f angleUnitCircle, Ball& ball);	// ������������ � ����� ������ �����
//	Vector2f BallCollisionRightBottomCorner(Vector2f angleUnitCircle, Ball& ball);	// ������������ � ������ ������ �����
//	Vector2f BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball);			// ������������ � ����� �������
//	Vector2f BallCollisionBottomWall(Vector2f angleUnitCircle, Ball& ball);			// ������������ � �����
//	Vector2f BallCollisionTopWall(Vector2f angleUnitCircle, Ball& ball);			// ������������ � ������
//	Vector2f BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball);			// ������������ � ������ �������
//
//public:
//	Block(BlockType blockType = NO_BONUS, bool bonus = false );
//	~Block() { }
//
//
//	Vector2f BallCollision(Vector2f angleUnitCircle, Ball& ball);
//
//	void BonusCreate();
//	
//
//};
//
