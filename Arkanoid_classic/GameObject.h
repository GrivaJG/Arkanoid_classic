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
	

	


public:
	//�����������
	GameObject();
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}

	//���������������� ���������
	GameObject operator=(const GameObject&) const = delete;
	GameObject operator+(const GameObject&) const = delete;

	//������
	FloatRect GetRect();
	
};

