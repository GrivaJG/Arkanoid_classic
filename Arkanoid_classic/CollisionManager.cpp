
#include "Event.h"
#include "Bullets.h"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "CollisionManager.h"





void CollisionManager::CollisionDetecter(list<Ball*>& balls, list<Block*>& blocks, list<Bullets*> bullets, ConcretePlatform& platform)
{

}


void CollisionManager::BallCollision(list<Ball*>& balls)
{
    list<Ball*>::iterator bl;

    for (bl = balls.begin(); bl != balls.end();)
    {
        // ѕровер€ем пересечение шарика с левой стенкой карты
        if ((*_bl)->GetRect().left < BORDER_LEFT)
        {
            (*_bl)->setPosition(BORDER_LEFT, (*_bl)->getPosition().y);  // ≈сли вдруг перелетели правую стенку, то уснатавливаемс€ в самое крайнее возможное положение
            (*_bl)->SetAngleUnitCircle(Vector2f(-(*_bl)->GetAngleUnitCircle().x, (*_bl)->GetAngleUnitCircle().y)); // ћен€ем направление на противоположное по х
            MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
        }

        // ѕровер€ем пересечение с правой стенкой
        if ((*_bl)->GetRect().left + (*_bl)->GetRect().width > BORDER_RIGHT)
        {
            // ≈сли вдруг перелетели правую стенку, то уснатавливаемс€ в самое крайнее возможное положение
            (*_bl)->setPosition(BORDER_RIGHT - (*_bl)->GetRect().width, (*_bl)->getPosition().y);
            (*_bl)->SetAngleUnitCircle(Vector2f(-(*_bl)->GetAngleUnitCircle().x, (*_bl)->GetAngleUnitCircle().y)); // ћен€ем направление на противоположное по х
            MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
        }

        // ѕровер€ем пересечение с потолком
        if ((*_bl)->getPosition().y < BORDER_TOP)
        {
            (*_bl)->setPosition((*_bl)->getPosition().x, BORDER_TOP); // ≈сли вдруг перелетели потолок, то устанавливаемс€ в саоме крайнее возможное положение
            (*_bl)->SetAngleUnitCircle(Vector2f((*_bl)->GetAngleUnitCircle().x, -(*_bl)->GetAngleUnitCircle().y)); // ћен€ем направление на противоположное по х
            MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
        }


        //----------------------------------------------------------------ѕровер€ем столкновение шарика с платформой, (обрабатываем в классе Platform)
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

        //----------------------------------------------------------------ѕровер€ем столкновение шарика с блоками, (обрабатываем в блкоах)

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


        // ≈сли шарик упал 
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