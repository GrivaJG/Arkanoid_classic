#pragma once

#include "GameObject.h"

#include "Platform.h"

class CreatorPlatform;
class Ball : public GameObject
{
private:

	Vector2f _angleUnitCircle;   // ������ ����������� ������ ������
	Vector2f _speed;			 // ������ ��������
	
	float _acceleration;		 // ����������� ���������

	bool _flagInit;				 // ������������� ����������� ��� ������� ������ � ��������� (������ ����)
	bool _flagMove;				 // ���� ������� ������

	
public:
	Ball(float acceleration = 0.5);
	~Ball() { }


	//������
	void Move(double angleUnitCircleX, double angleUnityCircleY, float time, CreatorPlatform* creatorPlatform);
	

	void SetSpeedFast();  //�������� �������
	void SetSpeedSlow();  //�������� �������

	//��������
	void SetFlagMove(bool flagMove) { this->_flagMove = flagMove; }	
	bool GetFlagMove() { return this->_flagMove; }

	void SetFlagInit(bool flagInit) { this->_flagInit = flagInit; }
	bool GetFlagInit() { return this->_flagInit; }

	void SetSpeed(float acceleration);
};
