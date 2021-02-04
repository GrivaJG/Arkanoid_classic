#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using std::string;

class GameObject
{
private:
	sf::Image image;
	sf::Texture texture;
	string path;



public:
	//�����������
	GameObject(const string& path);
	GameObject(const GameObject&) = delete;
	~GameObject() {}

	//���������������� ���������
	GameObject operator=(const GameObject& gmbj) const = delete;
	GameObject operator+(const GameObject& gmbj) const = delete;

	//������
	sf::Texture& GetTexture() { return texture; }
	void SetImage(string path);
};

class Platform : public sf::Sprite
{
private:
	GameObject* gmbj;					//��������� �� ����� ��� �������� ����������� � ��������
	int coordX, coordY, width, hight;  //���������� ������ ������� � ������
	

public:
	Platform(GameObject* gmbj, int cX, int cY, int w, int h);
	Platform(const Platform&) = delete;
	~Platform() { }


	
};

class Balls : public sf::Sprite
{
private:
	GameObject* gmbj;					//��������� �� ����� ��� �������� ����������� � ��������
	int coordX, coordY, width, hight;  //���������� ������ ������� � ������
	sf::Sprite ball;				//��� ������, ������ ��� ����� ����� ��������� �� �������� ����� ����� � main


	double startX, startY;         //���������� ��������� ����� 
	double distance;

public:
	Balls(GameObject* gmbj, int cX, int cY, int w, int h);
	Balls(const Balls&) = delete;
	~Balls() { }

	//������
	void Move(double dx, double dy, float time);
	void SetStartPosition(double StartX, double StartY);

};

