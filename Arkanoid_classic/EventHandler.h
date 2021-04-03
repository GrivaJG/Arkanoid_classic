
#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

class EventHandler
{
public:

	void CollisionBallWithLeftWall(Ball& ball);
	void CollisionBallWithRightWall(Ball& ball);
	void CollisionBallWithTop(Ball& ball);
	void CollisionBallWithBottom(Ball& ball, ConcretePlatform* platform);

	void CollisionBallWithPlatform(Ball& ball, ConcretePlatform* platform);
	void CollisionBallWithBlock(Ball& ball, Block& block, std::vector<Bonus*>& bonuses);

	void CollisionPlatformWithBonus(ConcretePlatform* platform, Bonus& bonus, std::vector<Ball*>& balls);

	void CollisionBulletsWithTop(Bullets& bullet);
	void CollisionBulletsWithBlock(Bullets& bullet, Block& block, std::vector<Bonus*>& bonuses);
};

#endif

