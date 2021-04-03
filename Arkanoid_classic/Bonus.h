
#ifndef _BONUS_H
#define _BONUS_H

#include "GameObject.h"
#include "Platform.h"

class Bonus : public GameObject
{
public:
	Bonus(Image& img, BlockType blockType, Vector2f startPosition);
	~Bonus() {}

	void Move(float time);

	// Obrabotka stolknoveniy s platformoy
	void CollisionWithPlatform(ConcretePlatform* platform, std::vector<Ball*>& ball);

	// Baff functions
	void MultipleBall(std::vector<Ball*>& ball);		 // Iz kazhdogo sharika v igre viletaet eshe dva sharika
	void ChangePlatform(ConcretePlatform* platform); // Random uvelichivaem ili umenshaem platformu
	void LaserOnBoard(ConcretePlatform* platform);	 // Add 10 bullets
	void ChangeSpeedBall(std::vector<Ball*>& ball);	 // Uskoryaem ili zamedlyaem sharik(i)
	void CatchBall(std::vector<Ball*>& ball);			 // Esly sharik na ecrane ostalsya odin on prikleevaetsya k platforme
	void AddLive();								     // add 1 lives

private:

	BlockType m_bonus_type;
	double m_speed_fall = 0.1;
};

#endif // _BONUS_H