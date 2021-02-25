

#ifndef _BONUS_H
#define _BONUS_H

#include "Config.h"
#include "GameObject.h"
#include "Platform.h"
#include "Menu.h"




class Bonus : public GameObject
{
private:

	BlockType _bonusType;
	double _speedFall = 0.1;

public:
	Bonus(BlockType blockType, Vector2f startPosition);
	~Bonus() {}

	void Move(float time);

	//��������� ������������ � ����������
	void CollisionWithPlatform(ConcretePlatform* platform, std::list<Ball*>& ball);

	//������� �����
	void MultipleBall(std::list<Ball*>& ball); // �� ������� ������ � ���� �������� ��� ��� ������
	void ChangePlatform(ConcretePlatform* platform);   // ����������� ��� ��������� ���������
	void LaserOnBoard(ConcretePlatform* platform);	   // ������������� ����� �� ���������
	void ChangeSpeedBall(std::list<Ball*>& ball); // �������� ��� ��������� �����(�)
	void CatchBall(std::list<Ball*>& ball);    // ���� ����� �� ������ ������� ����, �� ������������� � ���������
	void AddLive();							   // ���� ����� ��������� ���� ����� ������

	

};

#endif // _BONUS_H