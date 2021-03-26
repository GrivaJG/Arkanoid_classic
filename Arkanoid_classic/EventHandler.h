#pragma once


class EventHandler
{
public:

	void CollisionBallWithLeftWall(Ball& ball);
	void CollisionBallWithRightWall(Ball& ball);
	void CollisionBallWithTop(Ball& ball);
	void CollisionBallWithBottom(Ball& ball);
};

