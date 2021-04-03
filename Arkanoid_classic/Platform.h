
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "GameObject.h"
#include "Ball.h"


class Platform : public GameObject
{
public:
	Platform(Image& img) : GameObject(img) { m_bullets = 0; }
	virtual ~Platform() {};

	// Methods
	void Move(const float speed, const float time);
	void SetBullets() { m_bullets += 10; }
	void ReSetBullets() { m_bullets = 0; }
	void Fire() { m_bullets -= 2; }
	bool GetBullets() { return m_bullets; }

	// virtual methods
	virtual Vector2f CollisionWithBall(Ball& ball); // Function collision handler

protected:

	uint8_t m_bullets;

	Vector2f BallCollisionLeftEdge(Ball& ball);			
	Vector2f BallCollisionRightEdge(Ball& ball);		
	Vector2f BallCollisionStandart(Ball& ball);			
	Vector2f BallCollisionLeftWall(Ball& ball);			
	Vector2f BallCollisionRightWall(Ball& ball);			
	
	float CollisionLocation(Ball& ball);				// Opredelyaem coord stolknoveniya
};

//---------------------------------------LargePlatform
class LargePlatform : public Platform
{
public:
	LargePlatform(Image& img);
	~LargePlatform() {}

	virtual Vector2f CollisionWithBall(Ball& ball) override; // Pereopredelyaem obrabotku stolknoveniya s sharikom

private:
	Vector2f BallCollisionLeftEdgePlus(Ball& ball);
	Vector2f BallCollisionRightEdgePlus(Ball& ball);
	Vector2f BallCollisionCenter(Ball& ball);	
};


//----------------------------------------MiddlePlatform
class MediumPlatform : public Platform
{	
public:
	MediumPlatform(Image& img);
	~MediumPlatform() {}
};

//-----------------------------------------SmallPlatform
class SmallPlatform : public Platform
{
public:
	SmallPlatform(Image& img);
	~SmallPlatform(){}
};

//-------------------------------------------Class composition platform
class ConcretePlatform
{
public:
	ConcretePlatform(Image& img);
	~ConcretePlatform();

	Platform* GetInstance() { return m_concrete_platform; }

	void ChangePlatform(int sizePlatform);
	sizePlatform GetSizePlatform() { return m_size_platform; }

private:
	Image& m_image;

	Platform* m_concrete_platform = NULL;
	MediumPlatform* m_medium_platform = NULL;
	LargePlatform* m_large_platform = NULL;
	SmallPlatform* m_small_platform = NULL;

	sizePlatform m_size_platform;
};

#endif