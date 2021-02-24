
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "GameObject.h"
#include "Ball.h"


class Platform : public GameObject
{

protected:

	Vector2f BallCollisionLeftEdge(Vector2f angleUnitCircle, Ball& ball);			// ������ � ������� ����� ��������� � ����� ���� (0-8 �������)
	Vector2f BallCollisionRightEdge(Vector2f angleUnitCircle, Ball& ball);			// ������ � ������� ����� ��������� � ������ ���� (0-8 ������� � ������� ����)
	Vector2f BallCollisionStandart(Vector2f angleUnitCircle, Ball& ball);			// ������ � ������� ����� ���������
	Vector2f BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball);			// ������ � ����� ����� ���������
	Vector2f BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball);			// ������ � ������ ����� ���������
	
	float CollisionLocation(Ball& ball);											// ���������� ������� ������������ �� ���������
	

public:
	Platform() {}
	virtual ~Platform() {};

	
	// ������ ��� ���� �����������
	void Move(const float speed, const float time);
	//void CollisionWithBonus(Bonus& bonus); ������������ ��������� � �������


	// ����������� ������
	virtual Vector2f CollisionWithBall(Vector2f angleUnitCircle, Ball& ball); // ������� ������������ ������������
};

//---------------------------------------������� ���������

class LargePlatform : public Platform
{
private:
	
	Vector2f BallCollisionLeftEdgePlus(Vector2f angleUnitCircle, Ball& ball);
	Vector2f BallCollisionRightEdgePlus(Vector2f angleUnitCircle, Ball& ball);
	Vector2f BallCollisionCenter(Vector2f angleUnitCircle, Ball& ball);



public:
	LargePlatform();
	~LargePlatform() {}


	virtual Vector2f CollisionWithBall(Vector2f angleUnitCircle, Ball& ball) override; // �������������� ��������� ������������ � �������
	
};


//----------------------------------------������� ���������
class MediumPlatform : public Platform
{
private:
	
public:
	MediumPlatform();
	~MediumPlatform() {}
};

//-----------------------------------------��������� ���������

class SmallPlatform : public Platform
{
public:
	SmallPlatform();
	~SmallPlatform(){}

};

//-------------------------------------------����� ���������� ��������
class ConcretePlatform
{
private:
	Platform* _concretePlatform = NULL;
	MediumPlatform* _mediumPlatform = NULL;
	LargePlatform* _largePlatform = NULL;
	SmallPlatform* _smallPlatform = NULL;

public:
	ConcretePlatform();
	~ConcretePlatform();

	Platform* GetInstance() { return _concretePlatform; }

	void ChangePlatform(int sizePlatform);

};

#endif