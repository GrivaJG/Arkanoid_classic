

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

    void CollisionDetecter(list<Ball*>)
};



/*
//---------------------------------------------------------------��������� ��������
void Levels::CollisionDetecter()
{

   BallCollision(); // ��������� ������������ ������� � ��������� �����

   PlatformCollision(); // ��������� ������������ ��������� ���� � ����������

   BulletsCollision();  // ��������� ������������ ��������� ���� � ������

}

void Levels::BallCollision()
{
    for (_bl = _ball.begin(); _bl != _ball.end();)
    {
        // ��������� ����������� ������ � ����� ������� �����
        if ((*_bl)->GetRect().left < BORDER_LEFT)
        {
            (*_bl)->setPosition(BORDER_LEFT, (*_bl)->getPosition().y);  // ���� ����� ���������� ������ ������, �� ��������������� � ����� ������� ��������� ���������
            (*_bl)->SetAngleUnitCircle(Vector2f(-(*_bl)->GetAngleUnitCircle().x, (*_bl)->GetAngleUnitCircle().y)); // ������ ����������� �� ��������������� �� �
            MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
        }

        // ��������� ����������� � ������ �������
        if ((*_bl)->GetRect().left + (*_bl)->GetRect().width > BORDER_RIGHT)
        {
            // ���� ����� ���������� ������ ������, �� ��������������� � ����� ������� ��������� ���������
            (*_bl)->setPosition(BORDER_RIGHT - (*_bl)->GetRect().width, (*_bl)->getPosition().y);
            (*_bl)->SetAngleUnitCircle(Vector2f(-(*_bl)->GetAngleUnitCircle().x, (*_bl)->GetAngleUnitCircle().y)); // ������ ����������� �� ��������������� �� �
            MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
        }

        // ��������� ����������� � ��������
        if ((*_bl)->getPosition().y < BORDER_TOP)
        {
            (*_bl)->setPosition((*_bl)->getPosition().x, BORDER_TOP); // ���� ����� ���������� �������, �� ��������������� � ����� ������� ��������� ���������
            (*_bl)->SetAngleUnitCircle(Vector2f((*_bl)->GetAngleUnitCircle().x, -(*_bl)->GetAngleUnitCircle().y)); // ������ ����������� �� ��������������� �� �
            MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
        }


        //----------------------------------------------------------------��������� ������������ ������ � ����������, (������������ � ������ Platform)
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

                (*_bl)->setPosition(_platform->GetInstance()->GetRect().left + (*_bl)->GetCatchPositionX(), _platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT+1);
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

        //----------------------------------------------------------------��������� ������������ ������ � �������, (������������ � ������)

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


        // ���� ����� ���� 
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

void Levels::PlatformCollision()
{

//-------------------------------------------------------------------��������� ������������ ������ � ���������� (������������ � ���������)
//---------------------------------------------------------------------------------------���� ����� ������ ������ ������� �����, �� ������� ���

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
