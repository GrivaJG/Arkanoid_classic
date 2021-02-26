
#ifndef _BALL_H
#define _BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
private:
	static unsigned _ballCounter;
	Vector2f _angleUnitCircle;   // ������ ����������� ������ ������
	Vector2f _speed;			 // ������ ��������
	
	float _acceleration;		 // ����������� ���������

	bool _flagInit;				 // ������������� ����������� ��� ������� ������ � ��������� (������ ����)
	

	
public:
	Ball(Image& img, float acceleration = 0.5, bool flagInit = true);
	~Ball() { _ballCounter--; }


	//������
	void Move(double angleUnitCircleX, double angleUnityCircleY, float time);

	void SetSpeedFast();  // �������� �������
	void SetSpeedSlow();  // �������� �������
	
	void SetSpeed(float acceleration); // ������� ���������, ����� ����� ����� ���� ������ ������
	float GetSpeed() { return _acceleration; }


	void SetFlagInit(bool flagInit) { _flagInit = flagInit; }
	bool GetFlagInit() { return _flagInit; }

	void SetAngleUnitCircle(Vector2f angleUnitCircle) { _angleUnitCircle = angleUnitCircle; }
	Vector2f GetAngleUnitCircle() { return _angleUnitCircle; }

	static unsigned GetBallCount() { return _ballCounter; }

	

};



#endif // _BALL_H