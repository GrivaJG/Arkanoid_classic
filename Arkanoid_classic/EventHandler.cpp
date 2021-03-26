
#include "Ball.h"
#include "EventHandler.h"



void EventHandler::CollisionBallWithLeftWall(Ball& ball)
{
	ball.CollisionWithLeftWall();
}

void EventHandler::CollisionBallWithRightWall(Ball& ball)
{
	ball.CollisionWithRightWall();
}

void EventHandler::CollisionBallWithTop(Ball& ball)
{
	ball.CollisionWithTop();
}