#pragma once

#include "GameObject.h"

class Platform : public GameObject
{
	enum Type { smallPlatform, mediumPlatform, largePlatform };
	unsigned typePlatform = mediumPlatform;

	unsigned rightBorder = 684; // ������ ������� � ������� ���������, 765 � ������� � 715 � ���������, ��� ����� ��� ����, ����� ��� ������������ ������ ������ � �������
	//����� ��������� �� ������� ������. �������, ��������� �������.

public:
	Platform(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	virtual ~Platform() {}

	void ResetTypePlatform();
	void SetPlatform(bool choicePlatform);
	unsigned GetPlatformType() { return typePlatform; }

	unsigned GetRightBorder() { return rightBorder; }

	//����������� ������
	virtual void Move();
	virtual void Collision();
};

//---------------------------------------������� ���������

class LargePlatform : public Platform
{

};


//----------------------------------------������� ���������
class MediumPlatform : public Platform
{

};


//-----------------------------------------��������� ���������

class SmallPlatform : public Platform
{


};