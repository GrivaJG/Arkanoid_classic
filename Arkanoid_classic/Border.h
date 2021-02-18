#pragma once

#include "GameObject.h"

class Border : public GameObject
{
private:
	//����� ������ (���� � �����)
	Sprite _verticalWall;
	Sprite _horizontalWall;
	Sprite _leftTopCorner;
	Sprite _leftBottomCorner;
	Sprite _rightTopCorner;
	Sprite _rightBottomCorner;

	//���������� ���������� �� ���������� ��������
   //�� ������ ������ ����� �������� ��������� �������� � ������� ���������� �� ������ �������
   //������� ����� ������ ������� ������������� ���������� ������� ����������� � �������� ������
	//����� ����� ��� ����� ��������
	


public:
	//�����������
	Border(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	Border(const Border&) = delete;

	~Border() {}

	//���������������� ���������
	Border operator=(const GameObject& gmbj) const = delete;
	Border operator+(const GameObject& gmbj) const = delete;

	//������ ��������� �������� ������ �����
	Sprite GetLeftTopCorner(int posX, int posY);
	Sprite GetLeftBottomCorner(int posX, int posY);
	Sprite GetRightTopCorner(int posX, int posY);
	Sprite GetRightBottomCorner(int posX, int posY);
	Sprite GetVerticalWall(int posX, int posY);
	Sprite GetHorizontalWall(int posX, int posY);

	void CreateMap(RenderWindow& window);
	void CreateMenu(RenderWindow& window);


};

