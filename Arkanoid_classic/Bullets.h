
#ifndef _BULLETS_H
#define _BULLETS_H

#include "GameObject.h"
#include "Config.h"

class Bullets : public GameObject
{
	float _acceleration;


public:
	Bullets(Image& img, float acceleration = -0.7);
	~Bullets() {}

	void Move(float time);
};

#endif // !_BULLETS_H