
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
	
	bool _flagCatch;
	bool _flagBallCatchPosition;
	float _catchPositionX;
	unsigned _catchCounter;
	

	
public:
	Ball(Image& img, float acceleration = 0.3, bool flagInit = true);
	~Ball() { _ballCounter--; }


	//������
	void Move(double angleUnitCircleX, double angleUnityCircleY, float time);

	void SetSpeedFast();  // �������� �������
	void SetSpeedSlow();  // �������� �������
	
	void ResetSpeed(); // ������� ���������, ����� ����� ����� ���� ������ ������
	float GetSpeed() { return _acceleration; }


	void SetFlagInit(bool flagInit) { _flagInit = flagInit; }
	bool GetFlagInit() { return _flagInit; }

	void SetAngleUnitCircle(Vector2f angleUnitCircle) { _angleUnitCircle = angleUnitCircle; }
	Vector2f GetAngleUnitCircle() { return _angleUnitCircle; }

	void SetFlagCatch(bool flag) { _flagCatch = flag; }
	bool GetFlagCatch() { return _flagCatch; }

	void SetFlagBallCatchPosition(bool flag) { _flagBallCatchPosition = flag; }
	bool GetFlagBallCatchPosition() { return _flagBallCatchPosition; }

	void SetCatchPositionX(float catchPositionX) { _catchPositionX = catchPositionX; }
	float GetCatchPositionX() { return _catchPositionX; }

	void SetCatchCounter() { _catchCounter += 10; }
	void ResetCatch() { _catchCounter = 0; _flagBallCatchPosition = false; _flagCatch = false; }
	void DecreaseCatchCounter() { _catchCounter--; }
	unsigned GetCatchCounter() { return _catchCounter; }
	
	static unsigned GetBallCount() { return _ballCounter; }

	void BonusCatch();



	

};



#endif // _BALL_H