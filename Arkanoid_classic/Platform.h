
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "GameObject.h"
#include "Ball.h"



class Platform : public GameObject
{

protected:

	Vector2f BallCollisionLeftEdge(Ball& ball);			// ������ � ������� ����� ��������� � ����� ���� (0-8 �������)
	Vector2f BallCollisionRightEdge(Ball& ball);			// ������ � ������� ����� ��������� � ������ ���� (0-8 ������� � ������� ����)
	Vector2f BallCollisionStandart(Ball& ball);			// ������ � ������� ����� ���������
	Vector2f BallCollisionLeftWall(Ball& ball);			// ������ � ����� ����� ���������
	Vector2f BallCollisionRightWall(Ball& ball);			// ������ � ������ ����� ���������
	
	float CollisionLocation(Ball& ball);											// ���������� ������� ������������ �� ���������
	

public:
	Platform() {}
	virtual ~Platform() {};

	
	// ������ ��� ���� �����������
	void Move(const float speed, const float time);	


	// ����������� ������
	virtual Vector2f CollisionWithBall(Ball& ball); // ������� ������������ ������������
};

//---------------------------------------������� ���������

class LargePlatform : public Platform
{
private:
	
	Vector2f BallCollisionLeftEdgePlus(Ball& ball);
	Vector2f BallCollisionRightEdgePlus(Ball& ball);
	Vector2f BallCollisionCenter(Ball& ball);



public:
	LargePlatform();
	~LargePlatform() {}


	virtual Vector2f CollisionWithBall(Ball& ball) override; // �������������� ��������� ������������ � �������
	
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

	sizePlatform _sizePlatform;

public:
	ConcretePlatform();
	~ConcretePlatform();

	Platform* GetInstance() { return _concretePlatform; }

	void ChangePlatform(int sizePlatform);
	sizePlatform GetSizePlatform() { return _sizePlatform; }

};

#endif