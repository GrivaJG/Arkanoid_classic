#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <list>
#include  <random> //��� ������� ���������� ����������� ������ ������ ��� ������ ��� ������� � ���������





using std::string;
using namespace sf;


class GameObject : public Sprite
{
protected:

	Texture texture;
	bool isMove;

	float coordX, coordY, width, height;	//���������� ������� ����� �����, ������ � ������ �������
	float speedX;								//�������� �������� �� ���������� �
	float speedY;								//�������� �������� �� ���������� y



public:
	//�����������
	GameObject(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
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

class Platform : public GameObject
{
private:


public:
	Platform(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	~Platform() {}

};

class Balls : public GameObject
{
private:

	double angle_unit_circle_x = 0.0;  //����������� ������ ������ �� x
	double angle_unit_circle_y = 0.0;  //����������� ������ ������ �� y
	bool initialization = true;  //������������� ����������� ��� ������� ������ � ��������� (������ ����)
	bool change_angle = true;    //������������ ��� ��������� ���� � ������ Move
	int counter = 0;

public:
	Balls(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);

	Balls(const Balls&) = delete;
	~Balls() { }

	//������
	void Move(double unit_circle_x, double unit_circle_y, float time, Platform* platform);
	void ChangeVector(int x);

	void SetSpeedFast(int x);  //�������� �������
	void SetSpeedSlow(int x);  //�������� �������

	void SetIsMove(bool isMove) { this->isMove = isMove; }
	bool GetIsMove() { return this->isMove; }



};

class Block : public GameObject
{
private:
	int lives = 0;

public:
	Block(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	Block(const Block&) = delete;
	~Block() { }


	static bool Collision(std::list<Block*>& blocks, std::list<Block*>::iterator blks, Balls& ball);


};

