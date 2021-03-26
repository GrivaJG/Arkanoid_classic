
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

}


void CollisionManager::BallCollision()
{
    list<Ball*>::iterator bl;

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


        //----------------------------------------------------------------Проверяем столкновение шарика с платформой, (обрабатываем в классе Platform)
        if (_platform->GetInstance()->GetRect().intersects((*_bl)->GetRect()))
        {
            Menu::GetInstance().ResetCombo();


            if ((*_bl)->GetFlagCatch() && Ball::GetBallCount() == 1)
            {
                if (!(*_bl)->GetFlagBallCatchPosition())
                {
                    MusicAndSounds::GetInstance().BallCatchPlay();

                    (*_bl)->SetCatchPositionX((*_bl)->getPosition().x - _platform->GetInstance()->GetRect().left);
                    (*_bl)->SetFlagBallCatchPosition(true);
                    (*_bl)->DecreaseCatchCounter();
                }

                (*_bl)->setPosition(_platform->GetInstance()->GetRect().left + (*_bl)->GetCatchPositionX(), _platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT + 1);
            }
            else
            {
                MusicAndSounds::GetInstance().BallBounceOfPlatformPlay();
                (*_bl)->SetAngleUnitCircle(_platform->GetInstance()->CollisionWithBall(**_bl));

                if ((*_bl)->GetCatchCounter() > 0)
                {
                    (*_bl)->SetFlagCatch(true);
                }
            }


        }

        //----------------------------------------------------------------Проверяем столкновение шарика с блоками, (обрабатываем в блкоах)

        for (_blk = _block.begin(); _blk != _block.end();)
        {
            if ((*_blk)->GetRect().intersects((*_bl)->GetRect()))
            {
                Menu::GetInstance().SetCountScore(10 * Menu::GetInstance().GetCombo());
                Menu::GetInstance().IncreaseCombo();

                MusicAndSounds::GetInstance().BallBounceOfBlockPlay();

                (*_bl)->SetAngleUnitCircle((*_blk)->BallCollision(**_bl));
                if ((*_blk)->GetFlagBonus())
                {
                    _bonus.push_back(new Bonus(_image, (*_blk)->GetBlockType(), Vector2f((*_blk)->GetRect().left + (*_blk)->GetRect().width / 2 - BONUS_WIDTH / 2,
                        (*_blk)->getPosition().y)));
                }
                delete* _blk;
                _blk = _block.erase(_blk);
            }
            else
            {
                _blk++;
            }
        }


        // Если шарик упал 
        if ((*_bl)->getPosition().y > BORDER_BOTTOM)
        {
            BallFall();
        }
        else
        {
            _bl++;
        }
    }
}