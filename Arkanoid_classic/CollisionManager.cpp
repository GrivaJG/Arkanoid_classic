


#include "CollisionManager.h"

CollisionManager::CollisionManager(ConcretePlatform* platform, std::list<Ball*>& ball, std::list<Block*>& block, std::list<Bonus*>& bonus,
    std::list<Bullets*>& bullets) : m_platform(platform), m_balls(ball), m_blocks(block), m_bonuses(bonus), m_bullets(bullets)
{
    //Podpisivaemsya na sobitiya
    CollisionBallWithLeftWall += METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithLeftWall);
    CollisionBallWithRightWall += METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithRightWall);
    CollisionBallWithTop += METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithTop);
    CollisionBallWithBottom += METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithBottom);
    CollisionBallWithBlock += METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithBlock);
    CollisionBallWithPlatform += METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithPlatform);
    CollisionPlatformWithBonus += METHOD_HANDLER(event_handler, EventHandler::CollisionPlatformWithBonus);
    CollisionBulletsWithTop += METHOD_HANDLER(event_handler, EventHandler::CollisionBulletsWithTop);
    CollisionBulletsWithBlock += METHOD_HANDLER(event_handler, EventHandler::CollisionBulletsWithBlock);
}

CollisionManager::~CollisionManager()
{
    // Otpisivaemsya ot sobitiy
    CollisionBallWithLeftWall -= METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithLeftWall);
    CollisionBallWithRightWall -= METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithRightWall);
    CollisionBallWithTop -= METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithTop);
    CollisionBallWithBottom -= METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithBottom);
    CollisionBallWithBlock -= METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithBlock);
    CollisionBallWithPlatform -= METHOD_HANDLER(event_handler, EventHandler::CollisionBallWithPlatform);
    CollisionPlatformWithBonus -= METHOD_HANDLER(event_handler, EventHandler::CollisionPlatformWithBonus);
    CollisionBulletsWithTop -= METHOD_HANDLER(event_handler, EventHandler::CollisionBulletsWithTop);
    CollisionBulletsWithBlock -= METHOD_HANDLER(event_handler, EventHandler::CollisionBulletsWithBlock);
}



void CollisionManager::CollisionDetecter()
{
    BallCollision();     // All Collision with balls

    PlatformCollision(); // All Collision with platform

    BulletsCollision();  // Bullets collision with blocks and top
}


void CollisionManager::BallCollision()
{
    list<Ball*>::iterator bl;
    list<Block*>::iterator blk;

    for (bl = m_balls.begin(); bl != m_balls.end();)
    {
        // Intersection with left wall
        if ((*bl)->GetRect().left < BORDER_LEFT)
        {
            CollisionBallWithLeftWall(**bl);
        }

        // Intersection with right wall
        if ((*bl)->GetRect().left + (*bl)->GetRect().width > BORDER_RIGHT)
        {
            CollisionBallWithRightWall(**bl);
        }

        // Intersection with top
        if ((*bl)->getPosition().y < BORDER_TOP)
        {
            CollisionBallWithTop(**bl);
        }


        //---------------------------------------------------------------Collision balls with platform
        if (m_platform->GetInstance()->GetRect().intersects((*bl)->GetRect()))
        {
            CollisionBallWithPlatform(**bl, m_platform);
        }

        //----------------------------------------------------------------Collision ball with blocks

        for (blk = m_blocks.begin(); blk != m_blocks.end();)
        {
            if ((*blk)->GetRect().intersects((*bl)->GetRect()))
            {
                CollisionBallWithBlock(**bl, **blk, m_bonuses);
                delete* blk;
                blk = m_blocks.erase(blk);
            }
            else
            {
                blk++;
            }
        }


        //--------------------------------------------------------------------If ball fallen
        if ((*bl)->getPosition().y > BORDER_BOTTOM)
        {
            if (Ball::GetBallCount() <= 1)
            {
                CollisionBallWithBottom(**bl, m_platform);
                bl++;
            }
            else
            {
                delete* bl;
                bl = m_balls.erase(bl);
                MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
            }
        }
        else
        {
            bl++;
        }
    }
}



void CollisionManager::PlatformCollision()
{

    //-------------------------------------------------------------------Intersect Platform with bonus
    
    
    list<Bonus*>::iterator bns;

    for (bns = m_bonuses.begin(); bns != m_bonuses.end();)
    {
        if ((*bns)->GetRect().intersects(m_platform->GetInstance()->GetRect()))
        {
            CollisionPlatformWithBonus(m_platform, **bns, m_balls);
            delete* bns;
            bns = m_bonuses.erase(bns);
        }
        else if ((*bns)->getPosition().y > BORDER_BOTTOM) // If bonus intersect bottom then delete bonus
        {
            delete* bns;
            bns = m_bonuses.erase(bns);

        }
        else
        {
            bns++;
        }

    }
}

//-------------------------------------------------------------------Intersect Bullets with top and with blocks
void CollisionManager::BulletsCollision()
{
    std::list<Bullets*>::iterator blts;
    std::list<Block*>::iterator blk;

    for (blts = m_bullets.begin(); blts != m_bullets.end();)
    {
        if ((*blts)->getPosition().y < BORDER_TOP)
        {
            CollisionBulletsWithTop(**blts);
            delete* blts;
            blts = m_bullets.erase(blts);
            continue;
        }


        for (blk = m_blocks.begin(); blk != m_blocks.end();)
        {
            if ((*blts)->GetRect().intersects((*blk)->GetRect()))
            {
                CollisionBulletsWithBlock(**blts, **blk, m_bonuses);
                delete* blk;
                blk = m_blocks.erase(blk);

                delete* blts;
                blts = m_bullets.erase(blts);
                break;
            }
            else
            {
                blk++;
            }
        }

        if (!m_bullets.empty() && blts != m_bullets.end())
        {
            blts++;
        }

    }
}