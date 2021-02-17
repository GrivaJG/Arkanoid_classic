#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <list>
#include <random> //��� ������� ���������� ����������� ������ ������ ��� ������ ��� ������� � ���������
#include "Config.h" //������ ����������� �������� ������������

using std::string;
using namespace sf;

//---------------------------------------------Game Object--------------------------------------------------
class GameObject : public Sprite
{
protected:
	static Image image;
	Texture texture;
	bool isMove;

	float coordX, coordY, width, height;	//���������� ������� ����� �����, ������ � ������ �������
	float speedX;								//�������� �������� �� ���������� �
	float speedY;								//�������� �������� �� ���������� y



public:
	//�����������
	GameObject(float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}

	//���������������� ���������
	GameObject operator=(const GameObject&) const = delete;
	GameObject operator+(const GameObject&) const = delete;

	//������
	FloatRect GetRect();
	Vector2f GetSpeed();
	void SetSpeed(Vector2f speed);
};

//----------------------------------------------Platform--------------------------------------------------


//------------------------------------------------Balls--------------------------------------------------


//------------------------------------------------Bonus--------------------------------------------------


//------------------------------------------------Block--------------------------------------------------



