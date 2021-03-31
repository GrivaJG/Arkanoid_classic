#include "Bullets.h"


Bullets::Bullets(Image& img, float acceleration) : GameObject(img)
{
	this->setTexture(_texture);
	this->setTextureRect(IntRect(BULLET_LEFT, BULLET_TOP, BULLET_WIDTH, BULLET_HEIGHT));
	//this->setScale(0.4, 0.4);
	_acceleration = acceleration;
}

void Bullets::Move(float time)
{
	this->move(0, _acceleration * time);
}