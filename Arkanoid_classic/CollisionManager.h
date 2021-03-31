

#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

using std::list;

class CollisionManager
{
public:
    CollisionManager(ConcretePlatform* platform, std::list<Ball*>& ball, std::list<Block*>& block, std::list<Bonus*>& bonus,
        std::list<Bullets*>& bullets) : m_platform(platform), m_balls(ball), m_blocks(block), m_bonuses(bonus), m_bullets(bullets) {}
    ~CollisionManager() {}

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

    //Events

    //Events With Ball
    TEvent<Ball&> CollisionBallWithLeftWall;
    TEvent<Ball&> CollisionBallWithRightWall;
    TEvent<Ball&> CollisionBallWithTop;
    TEvent<Ball&, ConcretePlatform*> CollisionBallWithBottom;
    TEvent<Ball&, Block&, std::list<Bonus*>> CollisionBallWithBlock;
    TEvent<Ball&, ConcretePlatform*> CollisionBallWithPlatform;
    
    // Other Events
    TEvent<ConcretePlatform*, Bonus&, std::list<Ball*>&> CollisionPlatformWithBonus;
    TEvent<Bullets&> CollisionBulletsWithTop;
    TEvent<Bullets&, Block&, std::list<Bonus*>> CollisionBulletsWithBlock;
    
};



#endif // !COLLISION_MANAGER_H_
