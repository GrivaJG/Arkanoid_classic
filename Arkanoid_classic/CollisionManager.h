

#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include "Event.h"
#include "EventHandler.h"

using std::vector;

class CollisionManager
{
    
public:
    CollisionManager(ConcretePlatform* platform, std::vector<Ball*>& ball, std::vector<Block*>& block, std::vector<Bonus*>& bonus,
        std::vector<Bullets*>& bullets);
    ~CollisionManager();

    void CollisionDetecter();

private:

    ConcretePlatform* m_platform;    
    std::vector<Ball*>& m_balls;
    std::vector<Block*>& m_blocks;
    std::vector<Bonus*>& m_bonuses;
    std::vector<Bullets*>& m_bullets;

    void BallCollision();
    void PlatformCollision();
    void BulletsCollision();
   
    EventHandler event_handler;

    //Events With Ball
    TEvent<class Ball&> CollisionBallWithLeftWall;
    TEvent<class Ball&> CollisionBallWithRightWall;
    TEvent<class Ball&> CollisionBallWithTop;
    TEvent<class Ball&, ConcretePlatform*> CollisionBallWithBottom;
    TEvent<class Ball&, Block&, std::vector<Bonus*>&> CollisionBallWithBlock;
    TEvent<class Ball&, ConcretePlatform*> CollisionBallWithPlatform;
    
    // Other Events
    TEvent<class ConcretePlatform*, class Bonus&, std::vector<class Ball*>&> CollisionPlatformWithBonus;
    TEvent<class Bullets&> CollisionBulletsWithTop;
    TEvent<class Bullets&, class Block&, std::vector<class Bonus*>&> CollisionBulletsWithBlock;
    
};

#endif // !COLLISION_MANAGER_H_
