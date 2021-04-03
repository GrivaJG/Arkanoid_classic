
#ifndef BLOCK_H_
#define BLOCK_H_

#include "GameObject.h"

class Ball;
class Block : public GameObject
{
public:
	Block(Image& img, BlockType blockType = NO_BONUS, bool bonus = false);
	~Block() { }

	Vector2f BallCollision(Ball& ball);

	BlockType GetBlockType() { return m_block_type; }
	bool GetFlagBonus() { return m_flag_bonus; }

private:
	int m_strength = 0;			// Kolichestvo popadaniy v block do razrusheniya 
	
	bool m_flag_bonus = false;	// Esli True to posle razrusheniya blocka iz nego vipadaet bonus
	BlockType m_block_type;		// Color blocka otvechaet za podgruzhennuu texture and type bonusa kotoriy iz nee moget vipast

	Vector2f BallCollisionLeftTopCorner(Ball& ball);		// Collision with left top corner
	Vector2f BallCollisionRightTopCorner(Ball& ball);		// Collision with right top corner
	Vector2f BallCollisionLeftBottomCorner(Ball& ball);	    // Collision with left bottom corner
	Vector2f BallCollisionRightBottomCorner(Ball& ball);	// Collision with right bottom corner
	Vector2f BallCollisionLeftWall(Ball& ball);				// Collision with left wall
	Vector2f BallCollisionBottomWall(Ball& ball);			// Collision with bottom wall
	Vector2f BallCollisionTopWall(Ball& ball);				// Collision with top wall
	Vector2f BallCollisionRightWall(Ball& ball);			// Collision with right wall
};

#endif