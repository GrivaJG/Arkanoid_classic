#pragma once


#include "Config.h"
#include "GameObject.h"
#include "Ball.h"


class Block : public GameObject
{
private:
	
	

	int _strength = 0;    // Количество попаданий в блок до разрушения 
	
	bool _flagBonus = false;  // Если true то при попадании из блока выпадает бонус
	BlockType _blockType; // Цвет блока отвечает за подгуженную текстуру и тип бонуса который из нее может выпасть


	Vector2f BallCollisionLeftTopCorner(Ball& ball);		// Столкновение с левым верхним углом
	Vector2f BallCollisionRightTopCorner(Ball& ball);		// Столкновение с правым верхним углом
	Vector2f BallCollisionLeftBottomCorner(Ball& ball);	// Столкновение с левым нижним углом
	Vector2f BallCollisionRightBottomCorner(Ball& ball);	// Столкновение с правым нижним углом
	Vector2f BallCollisionLeftWall(Ball& ball);			// Столкновение с левой стенкой
	Vector2f BallCollisionBottomWall(Ball& ball);			// Столкновение с низом
	Vector2f BallCollisionTopWall(Ball& ball);			// Столкновение с верхом
	Vector2f BallCollisionRightWall(Ball& ball);			// Столкновение с правой стенкой

public:
	Block(Image& img, BlockType blockType = NO_BONUS, bool bonus = false );
	~Block() { }


	Vector2f BallCollision(Ball& ball);

	BlockType GetBlockType() { return _blockType; }
	bool GetFlagBonus() { return _flagBonus; }	

};

