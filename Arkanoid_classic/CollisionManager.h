

#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

using std::list;

class CollisionManager
{
public:
    CollisionManager(ConcretePlatform* platform, std::list<Ball*>& ball, std::list<Block*>& block, std::list<Bonus*>& bonus,
        std::list<Bullets*>& bullets) : m_platform(platform), m_ball(ball), m_block(block), m_bonus(bonus), m_bullets(bullets) {}
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
    TEvent<Ball&> CollisionBallWithLeftWall;
    TEvent<Ball&> CollisionBallWithRightWall;
    TEvent<Ball&> CollisionBallWithTop;
    TEvent<Ball&> CollisionBallWithBottom;

    TEvent<Ball&, ConcretePlatform*> CollisionBallWithPlatform;

    TEvent<Ball&, Block&> CollisionBallWithBlock;

    TEvent<ConcretePlatform*, Bonus&> CollisionPlatformWithBonus;

    TEvent<Bullets&> CollisionBulletsWithTop;
    TEvent<Bullets&, Block&> CollisionBulletsWithTop;
    
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
