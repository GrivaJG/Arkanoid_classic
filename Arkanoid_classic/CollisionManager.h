

#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

using std::list;

class CollisionManager
{
public:
    TEvent<> m_Collision_Ball_With_Left_Wall;
    TEvent<> m_Collision_Ball_With_Right_Wall;
    TEvent<> m_Collision_Ball_With_Top;
    TEvent<> m_Collision_Ball_With_Platform;
    TEvent<> m_Collision_Ball_Wtih_Block;
    TEvent<> m_Collision_Ball_Is_Fall;

    TEvent<> m_Collision_Platform_With_Bonus;

    TEvent<> m_Collision_Bullets_With_Top;
    TEvent<> m_Collision_Bullets_With_Block;

    void CollisionDetecter(list<Ball*>& balls, list<Block*>& blocks, list<Bullets*> bullets, ConcretePlatform& platform);

private:

    void BallCollision(list<Ball*>& balls);
    void PlatformCollision();
    void BulletsCollision();

};



/*
//---------------------------------------------------------------Обработка коллизий
void Levels::CollisionDetecter()
{

   BallCollision(); // Проверяем столкновение шариков с границами карты

   PlatformCollision(); // Проверяем столкновения элементов игры с платформой

   BulletsCollision();  // Проверяем столкновения элементов игры с пулями

}



void Levels::PlatformCollision()
{

//-------------------------------------------------------------------Проверяем столкновение бонуса с платформой (обрабатываем в платформе)
//---------------------------------------------------------------------------------------Если бонус достиг нижней границы карты, то удаляем его

    for (_bns = _bonus.begin(); _bns != _bonus.end();)
    {
        if ((*_bns)->GetRect().intersects(_platform->GetInstance()->GetRect()))
        {
            MusicAndSounds::GetInstance().PlatformCollBonusPlay();
            (*_bns)->CollisionWithPlatform(_platform, _ball);
            delete* _bns;
            _bns = _bonus.erase(_bns);
        }
        else if ((*_bns)->getPosition().y > BORDER_BOTTOM)
        {
            delete* _bns;
            _bns = _bonus.erase(_bns);

        }
        else
        {
            _bns++;
        }

    }
}

void Levels::BulletsCollision()
{
    for (_blts = _bullets.begin(); _blts != _bullets.end();)
    {
        if ((*_blts)->getPosition().y < BORDER_TOP)
        {
            MusicAndSounds::GetInstance().BulletsHitBorderMapPlay();
            delete* _blts;
            _blts = _bullets.erase(_blts);
            continue;
        }

    
        for (_blk = _block.begin(); _blk != _block.end();)
        {
            if ((*_blts)->GetRect().intersects((*_blk)->GetRect()))
            {
                MusicAndSounds::GetInstance().BulletsHitBlockPlay();
                if ((*_blk)->GetFlagBonus())
                {
                    _bonus.push_back(new Bonus(_image, (*_blk)->GetBlockType(), Vector2f((*_blk)->GetRect().left + (*_blk)->GetRect().width / 2 - BONUS_WIDTH / 2,
                        (*_blk)->getPosition().y)));
                }

                delete* _blk;
                _blk = _block.erase(_blk);

                delete* _blts;
                _blts = _bullets.erase(_blts);
                break;
            }
            else
            {
                _blk++;
            }
        } 

        if (!_bullets.empty() && _blts != _bullets.end())
        {
            _blts++;
        }
            
    }
}*/

#endif // !COLLISION_MANAGER_H_
