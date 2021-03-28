
#include "Event.h"
#include "Bullets.h"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "Bonus.h"
#include "MusicAndSounds.h"
#include "CollisionManager.h"





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

