
#ifndef _BALL_H
#define _BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball(Image& img, float acceleration = 0.3, bool flag_init = true);
	~Ball() { m_ball_counter--; }


	//Methods
	void Move(double angle_unit_circleX, double angle_unity_circleY, float time);

	void SetSpeedFast();
	void SetSpeedSlow();

	void ResetSpeed();
	float GetSpeed() { return m_acceleration; }


	// Properties
	void SetFlagInit(bool flagInit) { m_flag_init = flagInit; }
	bool GetFlagInit() { return m_flag_init; }

	void SetAngleUnitCircle(Vector2f angle_unit_circle) { m_angle_unit_circle = angle_unit_circle; }
	Vector2f GetAngleUnitCircle() { return m_angle_unit_circle; }

	void SetFlagCatch(bool flag) { m_flag_catch = flag; }
	bool GetFlagCatch() { return m_flag_catch; }

	void SetFlagBallCatchPosition(bool flag) { m_flag_ball_catch_position = flag; }
	bool GetFlagBallCatchPosition() { return m_flag_ball_catch_position; }

	void SetCatchPositionX(float catch_positionX) { m_catch_positionX = catch_positionX; }
	float GetCatchPositionX() { return m_catch_positionX; }

	void SetCatchCounter() { m_catch_counter += 10; }
	void ResetCatch() { m_catch_counter = 0; m_flag_ball_catch_position = false; m_flag_catch = false; }
	void DecreaseCatchCounter() { m_catch_counter--; }
	uint32_t GetCatchCounter() { return m_catch_counter; }

	static uint32_t GetBallCount() { return m_ball_counter; }

	void CollisionWithLeftWall();
	void CollisionWithRightWall();
	void CollisionWithTop();

private:
	static uint16_t m_ball_counter;  // Kolichestvo sozdannih sharov
	Vector2f m_angle_unit_circle;    // Vector napravleniya poleta sharika
	Vector2f m_speed;			     // SpeedVector
	
	float m_acceleration;		     // Acceleration factor

	bool m_flag_init;			     // Ball init for first flight
	
	bool m_flag_catch;			     // Ball catch to the platform
	bool m_flag_ball_catch_position; 
	float m_catch_positionX;	     // Position in platform when ball catch
	uint32_t m_catch_counter;        // Kolichestvo prilipaniy k platforme, kogda m_catch_counter == 0 sharik perestaet prilipat k platforme
};

#endif // _BALL_H