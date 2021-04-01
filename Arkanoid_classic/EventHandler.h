#pragma once


class EventHandler
{
public:

	void CollisionBallWithLeftWall(Ball& ball);
	void CollisionBallWithRightWall(Ball& ball);
	void CollisionBallWithTop(Ball& ball);
	void CollisionBallWithBottom(Ball& ball, ConcretePlatform* platform);

	void CollisionBallWithPlatform(Ball& ball, ConcretePlatform* platform);
	void CollisionBallWithBlock(Ball& ball, Block& block, std::list<Bonus*>& bonuses);

	void CollisionPlatformWithBonus(ConcretePlatform* platform, Bonus& bonus, std::list<Ball*>& balls);

	void CollisionBulletsWithTop(Bullets& bullet);
	void CollisionBulletsWithBlock(Bullets& bullet, Block& block, std::list<Bonus*>& bonuses);
};

