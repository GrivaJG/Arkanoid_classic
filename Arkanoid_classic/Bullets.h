
#ifndef _BULLETS_H
#define _BULLETS_H

#include "GameObject.h"

class Bullets : public GameObject
{
public:
	Bullets(Image& img, float acceleration = -0.7);
	~Bullets() {}

	void Move(float time);

private:
	float m_acceleration;
};
#endif // !_BULLETS_H