
#include "Config.h"
#include "Bullets.h"


Bullets::Bullets(Image& img, float acceleration) : GameObject(img)
{
	this->setTexture(m_texture);
	this->setTextureRect(IntRect(BULLET_LEFT, BULLET_TOP, BULLET_WIDTH, BULLET_HEIGHT));	
	m_acceleration = acceleration;
}

void Bullets::Move(float time)
{
	this->move(0, m_acceleration * time);
}