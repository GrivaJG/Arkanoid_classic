
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "GameObject.h"
#include "Ball.h"



class Ball;

class Platform : public GameObject
{

protected:

	Vector2f BallCollisionLeftEdge(Vector2f angleUnitCircle, Ball& ball);			// ������ � ������� ����� ��������� � ����� ���� (0-8 �������)
	Vector2f BallCollisionRightEdge(Vector2f angleUnitCircle, Ball& ball);			// ������ � ������� ����� ��������� � ������ ���� (0-8 ������� � ������� ����)
	Vector2f BallCollisionStandart(Vector2f angleUnitCircle, Ball& ball);			// ������ � ������� ����� ���������
	Vector2f BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball);
	Vector2f BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball);
	
	float CollisionLocation(Ball& ball);

public:
	Platform() {}
	virtual ~Platform() {};

	
	// ������ ��� ���� �����������
	void Move(const float speed, const float time);
	//void CollisionWithBonus(Bonus& bonus);



	// ����������� ������
	virtual Vector2f CollisionWithBall(Vector2f angleUnitCircle, Ball& ball); // C����������� � �������
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


	virtual Vector2f CollisionWithBall(Vector2f angleUnitCircle, Ball& ball) override; // �������������� ������������ � �������

};


//----------------------------------------������� ���������
class MediumPlatform : public Platform
{
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


//---------------------------------------------������ ����������� ������
class CreatorPlatform
{
	Platform* concretePlatform;
	
	

public:
	virtual ~CreatorPlatform() {};
	virtual Platform* FactoryMethod() const = 0;

	

	
	void ChangePlatform();	
	void SomeDraw(RenderWindow& window);
	
	Platform* GetInstance() { return this->concretePlatform; }

};

class CreatorSmallPlatform : public CreatorPlatform
{
public:
	Platform* FactoryMethod() const override
	{
		return new SmallPlatform();
	}
};

class CreatorMediumPlatform : public CreatorPlatform
{
public:
	Platform* FactoryMethod() const override
	{
		return new MediumPlatform();
	}
};

class CreatorLargePlatform : public CreatorPlatform
{
public:
	Platform* FactoryMethod() const override
	{
		return new LargePlatform();
	}
	
};

#endif