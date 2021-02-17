#pragma once

#include "GameObject.h"

class Balls : public GameObject
{
private:

	double angle_unit_circle_x = 0.0;  //����������� ������ ������ �� x
	double angle_unit_circle_y = 0.0;  //����������� ������ ������ �� y
	bool initialization = true;  //������������� ����������� ��� ������� ������ � ��������� (������ ����)
	bool change_angle = true;    //������������ ��� ��������� ���� � ������ Move
	unsigned score_ratio = 1;

	float speed_vector_x = 0; //������ �������� �� x
	float speed_vector_y = 0; //������ �������� �� y



	float ball_center_x = 0;    // ����� ������ �� �
	float ball_center_y = 0;    // ����� ������ �� y
	float ball_right_x = 0;     // ������ ���� �� �
	float ball_left_x = 0;      // ����� ���� �� �

	float platform_left_x = 0;  // ����� ���� ��������� �� � ��� ����� ������� �����������! ���������
	float platform_right_x = 0;	// ������ ���� ��������� �� � ��� ����� ������� �����������! ���������
	float platform_top_y = 0;   // ���� ���������

	bool greenBonus = false; //������� �� ��������� �����, ������� ������ ��� � �����

	int ballPositionOnPlatform = 37; //������� ������ ������������ ��������� �� �



	void CollisionLargePlatform(Platform* platform);
	void CollisionSmallAndMediumPlatform(Platform* platform);




public:
	Balls(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);

	Balls(const Balls&) = delete;
	~Balls() { }

	//������
	void Move(double unit_circle_x, double unit_circle_y, float time, Platform* platform);
	void ChangeVector(int x);

	void SetSpeedFast(int x);  //�������� �������
	void SetSpeedSlow(int x);  //�������� �������


	void IncreaseValue_ScoreRatio() { this->score_ratio += 1; }
	unsigned GetScoreRatio() { return score_ratio; }

	void SetIsMove(bool isMove) { this->isMove = isMove; }
	bool GetIsMove() { return this->isMove; }

	void SetGreenBonus() { greenBonus = true; }
	void ResetGreenBonus() { greenBonus = false; }
	void SetBallPositionOnPlatform(int x) { ballPositionOnPlatform = x; }
	void ResetBallPositionOnPlatform() { ballPositionOnPlatform = 37; }
	int GetBallPositionOnPlatform() { return ballPositionOnPlatform; }






};