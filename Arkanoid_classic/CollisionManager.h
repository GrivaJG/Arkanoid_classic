

#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include "Bullets.h"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "Bonus.h"
#include "MusicAndSounds.h"
#include "EventHandler.h"
#include "Event.h"

using std::list;


class CollisionManager
{
    
public:
    CollisionManager(ConcretePlatform* platform, std::list<Ball*>& ball, std::list<Block*>& block, std::list<Bonus*>& bonus,
        std::list<Bullets*>& bullets);
    ~CollisionManager();

    void CollisionDetecter();

private:

    ConcretePlatform* m_platform;    
    std::list<Ball*>& m_balls;
    std::list<Block*>& m_blocks;
    std::list<Bonus*>& m_bonuses;
    std::list<Bullets*>& m_bullets;

    void BallCollision();
    void PlatformCollision();
    void BulletsCollision();

    //EventHandler
    EventHandler event_handler;

    //Events With Ball
    TEvent<class Ball&> CollisionBallWithLeftWall;
    TEvent<class Ball&> CollisionBallWithRightWall;
    TEvent<class Ball&> CollisionBallWithTop;
    TEvent<class Ball&, ConcretePlatform*> CollisionBallWithBottom;
    TEvent<class Ball&, Block&, std::list<Bonus*>> CollisionBallWithBlock;
    TEvent<class Ball&, ConcretePlatform*> CollisionBallWithPlatform;
    
    // Other Events
    TEvent<class ConcretePlatform*, class Bonus&, std::list<class Ball*>&> CollisionPlatformWithBonus;
    TEvent<class Bullets&> CollisionBulletsWithTop;
    TEvent<class Bullets&, class Block&, std::list<class Bonus*>> CollisionBulletsWithBlock;
    
};



#endif // !COLLISION_MANAGER_H_
