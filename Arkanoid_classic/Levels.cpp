
#include "Levels.h"


unsigned Ball::_ballCounter = 0;

Levels::Levels(Image& img) : _image(img)
{
    _platform = new ConcretePlatform(_image);
    _platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    _ball.push_back(new Ball(_image));
    _bl = _ball.begin();
    (*_bl)->setPosition(BALL_START_POSITION);

    _level = 1;
    _changeLevel = true;
    _flagBallMove = false;

    
   
    

}

Levels::~Levels()
{
    delete _platform;
    
    while (!_block.empty())
    {
        _blk = _block.begin();
        delete* _blk;
        _blk = _block.erase(_blk);
    }

    while (!_bonus.empty())
    {
        _bns = _bonus.begin();
        delete* _bns;
        _bns = _bonus.erase(_bns);
    }

    while (!_ball.empty())
    {
        _bl = _ball.begin();
        delete* _bl;
        _bl = _ball.erase(_bl);
    }
}



int Levels::StartGame(RenderWindow& window)
{
    Menu::GetInstance().CreateStartMenu(window);                        // ������� ��������� �����
    Menu::GetInstance().CreateLevelSplashCreen(window, _board, _level); // ��������� ����� � ��������� ������
    GameInit();                                                         // �������� ��� �������� � ��������� ����������
    Menu::GetInstance().PlayerInit();                                   // ������ ����, ������������� ����� ������, � ���������� ����� � ��������� ��������.
   

    //������������� ���������� ����� ��� ������ ����� ��������, ����� ��� ����, ����� ��� ������� ������ � ������ ����
    //�� ������� �� ��������� ����������
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double angleUnitCircleX = 0;         // ���������� � ������� ����� ��������� ����������� �������� ������ (������ �� ��������� ����������)
    double angleUnitCircleY = 0;         

    // �������������� ���������� ������� ����� �������� ����� � ������������� ���
    Clock clockForBullets;
    Clock clock;

    while (window.isOpen())
    {   
        // ���� ���������� ��������� ������� 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float timeForBullet = clockForBullets.getElapsedTime().asMilliseconds();  // ������� ������ ��� ������� ����

        //---------------------------------------------��������� ������� ������� ������
        sf::Event event;
        while (window.pollEvent(event))
        {
            // ��������� ���� ���� ������ ������� Esc ��� ������� � ������ ������� ����
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            // ��������� ������� ������������ ������� ������� ������
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Space)
                {
                    // ����� ������� ������� ������ ���� ����� ������ ���������� _flagBallMove;
                    if (!_flagBallMove)
                    {
                        // ��������� ��������� ����������� �������� ������ ��� ������ ��������� ����������
                        angleUnitCircleX = (mersenne() % 150);
                        angleUnitCircleX = (angleUnitCircleX - 75) / 100;
                        angleUnitCircleY = sqrt(1.0 - pow(angleUnitCircleX, 2));
                        angleUnitCircleY = -1 * abs(angleUnitCircleY);

                        // �� ������� � ���� ���� �� ��������� �������������
                        _flagBallMove = true;

                        
                    }

                    for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                    {   
                        if ((*_bl)->getPosition().y == _platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT + 1)
                        {
                            (*_bl)->SetFlagCatch(false);
                            (*_bl)->SetFlagBallCatchPosition(false);
                        }
                    }                    
                }
                if (event.key.code == Keyboard::X)
                {
                    for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                    {
                        (*_bl)->SetSpeedFast();
                    }
                    
                }


                if (event.key.code == Keyboard::Z)
                {
                     for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                    {
                        (*_bl)->SetSpeedSlow();
                    }
                }

                if (event.key.code == Keyboard::F)
               {    
                    _platform->ChangePlatform(3);                    
               }
            }
        }


        //-------------------------------------------�������� �������������� ���������

        // ���� ������ ����� �������� ����, ������� ����
        if (_platform->GetInstance()->GetBullets() > 0)
        {
            if (timeForBullet > 1000)
            {
                _platform->GetInstance()->Fire();
                clockForBullets.restart();

                Bullets* tempBullet1 = new Bullets(_image);
                Bullets* tempBullet2 = new Bullets(_image);

                tempBullet1->setPosition(_platform->GetInstance()->GetRect().left, _platform->GetInstance()->GetRect().top +
                    _platform->GetInstance()->GetRect().height / 2 - BULLET_HEIGHT / 2);

                tempBullet2->setPosition(_platform->GetInstance()->GetRect().left + _platform->GetInstance()->GetRect().width - BULLET_WIDTH,
                    _platform->GetInstance()->GetRect().top + _platform->GetInstance()->GetRect().height / 2 - BULLET_HEIGHT / 2);


                _bullets.push_back(tempBullet1);
                _bullets.push_back(tempBullet2);

            }
        }


        //-------------------------------------------------�������� ���������

        // �������� ���������
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // ��������� �����, ���� ���������� � �� ������ ������ 25,
            // ��� ������� ������������, ���� ��������� �� ������������� ������� � ��������� ��������� ���������
            _platform->GetInstance()->Move(-0.5, time);
            if (_platform->GetInstance()->GetRect().left < BORDER_LEFT)
            {   
                _platform->GetInstance()->setPosition(Vector2f(BORDER_LEFT, PLATFORM_START_POSITION.y));
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // ��������� �����, ���� ���������� � �� ������ ������ 25,
            // ��� ������� ������������, ���� ��������� �� ������������� ������� � ��������� ��������� ���������
            _platform->GetInstance()->Move(0.5, time);
            if (_platform->GetInstance()->GetRect().left + _platform->GetInstance()->GetRect().width > BORDER_RIGHT)
            {
                _platform->GetInstance()->setPosition(Vector2f(BORDER_RIGHT - _platform->GetInstance()->GetRect().width, PLATFORM_START_POSITION.y));
            }
        }

        
        // ���� ���� �������� ��������� �������� ������
        if (_flagBallMove)
        {
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            (*_bl)->Move(angleUnitCircleX, angleUnitCircleY, time);
        }
        // ���� ���� �� �������� ����� �������� � ���������
        else
        {      
            // ������ �������: "�" ������ ������ �� �������� ���������
            _bl = _ball.begin();
            (*_bl)->setPosition((_platform->GetInstance()->GetRect().left +
                (_platform->GetInstance()->GetRect().width / 2) - ((*_bl)->GetRect().width / 2)),
                // ������ �������: "y" ������ ������ ���� ��������� �� ������ ������
                _platform->GetInstance()->GetRect().top - (*_bl)->GetRect().height);
        }

        // ������� ������
        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
        {
            (*_bns)->Move(time);
        }

        // ������� ����
        for (_blts = _bullets.begin(); _blts != _bullets.end(); _blts++)
        {
            (*_blts)->Move(time);
        }

        
        // ����� ���� ����������� ��������� ������������
        CollisionDetecter();

        // ���� ����� ����������� ������� ����� ��������� ����, ��� ���������� �������� � ���������� ��������
        if (Menu::GetInstance().GetCountlives() <= 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, _block, _board, _platform);
            Menu::GetInstance().PlayerInit();
            GameInit();

            _level = 1;
            _changeLevel = true;

            return 0;
        }

        if (_changeLevel) //���� ������ ��������� = true ���������� ������� ����� �������
        {
            
            _level = InitLevel(_level);
            _changeLevel = false;

        }

        if (_block.empty())
        {
            _changeLevel = true;
            _level++;
            GameInit();
            Menu::GetInstance().CreateLevelSplashCreen(window, _board, _level);
        }

       


        window.clear();

        _board.CreateMap(window);
        _board.CreateMenu(window);
        
        Menu::GetInstance().CreateMenu(window, _level);

        for (_blk = _block.begin(); _blk != _block.end(); _blk++)
            window.draw(**_blk);

        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
            window.draw(**_bns);

        for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            window.draw(**_bl);

        for (_blts = _bullets.begin(); _blts != _bullets.end(); _blts++)
        {
            window.draw(**_blts);
        }
             
        window.draw(*_platform->GetInstance());
       
        window.display();


    }

    
    return 0;
}
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
        }

        // ��������� ����������� � ������ �������
        if ((*_bl)->GetRect().left + (*_bl)->GetRect().width > BORDER_RIGHT)
        {
            // ���� ����� ���������� ������ ������, �� ��������������� � ����� ������� ��������� ���������
            (*_bl)->setPosition(BORDER_RIGHT - (*_bl)->GetRect().width, (*_bl)->getPosition().y);
            (*_bl)->SetAngleUnitCircle(Vector2f(-(*_bl)->GetAngleUnitCircle().x, (*_bl)->GetAngleUnitCircle().y)); // ������ ����������� �� ��������������� �� �
        }

        // ��������� ����������� � ��������
        if ((*_bl)->getPosition().y < BORDER_TOP)
        {
            (*_bl)->setPosition((*_bl)->getPosition().x, BORDER_TOP); // ���� ����� ���������� �������, �� ��������������� � ����� ������� ��������� ���������
            (*_bl)->SetAngleUnitCircle(Vector2f((*_bl)->GetAngleUnitCircle().x, -(*_bl)->GetAngleUnitCircle().y)); // ������ ����������� �� ��������������� �� �
        }


        //----------------------------------------------------------------��������� ������������ ������ � ����������, (������������ � ������ Platform)
        if (_platform->GetInstance()->GetRect().intersects((*_bl)->GetRect()))
        {
            Menu::GetInstance().ResetCombo();

            if ((*_bl)->GetFlagCatch() && Ball::GetBallCount() == 1)
            {
                if (!(*_bl)->GetFlagBallCatchPosition())
                {
                    (*_bl)->SetCatchPositionX((*_bl)->getPosition().x - _platform->GetInstance()->GetRect().left);
                    (*_bl)->SetFlagBallCatchPosition(true);
                    (*_bl)->DecreaseCatchCounter();
                }

                (*_bl)->setPosition(_platform->GetInstance()->GetRect().left + (*_bl)->GetCatchPositionX(), _platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT+1);
            }
            else
            {
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
            delete* _blts;
            _blts = _bullets.erase(_blts);
            continue;
        }

    
        for (_blk = _block.begin(); _blk != _block.end();)
        {
            if ((*_blts)->GetRect().intersects((*_blk)->GetRect()))
            {
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
}

//----------------------------------------------------------------�������� �������

int Levels::InitLevel(int lvl)
{
    switch (lvl)
    {
    case 1:
        return CreateLevel4();
        break;
    case 2:
        return CreateLevel2();
        break;
    case 3:
        return CreateLevel3();
        break;
    default:
        break;
    }



}

int Levels::CreateLevel1()
{
    int positionX = 0; //�������� �� �������
    int positionY = 0; //�������� �� ���

    //������ ���
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 5 || i == 7)
        {
            _block.push_back(new Block(_image, YELLOW, true));  // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, YELLOW));
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������ ���
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            _block.push_back(new Block(_image, GREEN, true));  // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    //������ ���
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 3 || i == 9)
        {
            _block.push_back(new Block(_image, PINK, true));  //������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, PINK));
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ��������� ���
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 2 || i == 10)
        {
            _block.push_back(new Block(_image, PURPLE, true));                    //������� �������� �����
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, PURPLE));
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    // ����� ���
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 1 || i == 11)
        {
            _block.push_back(new Block(_image, RED, true));  //������� �������� �����
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, RED));
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }
    //������ ���
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            _block.push_back(new Block(_image, BLUE, true));  //������� �������� �����
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, BLUE));
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������� ���
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        _block.push_back(new Block(_image, ORANGE));
        _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
        _blk--;                                                         //��������� �� ��������� �������.
        (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
       
    }
   
    return 1;
}

int Levels::CreateLevel2()
{   
    int positionX = 0;
    int positionY = 0;

    // ������ ���
    _block.push_back(new Block(_image, ORANGE));
    _blk = _block.end();                                             // �������� ������������� �� ����� ������� �� ��������� ��������� �����
    _blk--;                                                          // ��������� �� ��������� �������.
    (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23);  // ������������� ������� �����
    

    // ������ ���
    positionY = 1;
    for (int i = 0; i < 3; i++)
    {
        positionX = i;
        if (i == 2)
        {
            _block.push_back(new Block(_image, PURPLE, true));              // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, PURPLE));                    // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������ ���
    positionY = 2;
    for (int i = 0; i < 5; i++)
    {
        positionX = i;
        if (i == 4)
        {
            _block.push_back(new Block(_image, PINK, true));                // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, PINK));                      // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ��������� ���
    positionY = 3;
    for (int i = 0; i < 7; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, YELLOW, true));              // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, YELLOW));                    // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ����� ���
    positionY = 4;
    for (int i = 0; i < 9; i++)
    {
        positionX = i;
        if (i == 8)
        { 
            _block.push_back(new Block(_image, RED, true));                 // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, RED));                       // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������ ���
    positionY = 5;
    for (int i = 0; i < 11; i++)
    {
        positionX = i;
        if (i == 10)
        {
            _block.push_back(new Block(_image, BLUE, true));                // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, BLUE));                      // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������� ���
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 12)
        {
            _block.push_back(new Block(_image, GREEN, true));               // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));                     // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    return 2;
}

int Levels::CreateLevel3()
{
    int positionX = 0;
    int positionY = 0;

    // ������ ���
    positionY = 0;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, PURPLE, true));              // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, PURPLE));                    // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������ ���
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            _block.push_back(new Block(_image, GREEN, true));               // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));                     // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������ ���
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            _block.push_back(new Block(_image, YELLOW, true));                // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, YELLOW));                      // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ��������� ���
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 2 || i == 10)
        {
            _block.push_back(new Block(_image, BLUE, true));              // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, BLUE));                    // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ����� ���
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        {
            _block.push_back(new Block(_image, ORANGE));                       // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������ ���
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            _block.push_back(new Block(_image, RED, true));                // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, RED));                      // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������� ���
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, PINK, true));               // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, PINK));                     // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    return 3;
}

int Levels::CreateLevel4()
{
    int positionX = 0;
    int positionY = 0;

    // ������ ���
    positionY = 0;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, BLUE, true));                // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }        
    }

    // ������ ���
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i > 4 && i < 7)
        {
            _block.push_back(new Block(_image, RED));               // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(67 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }        
    }

    // ������ ���
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, PINK, true));                // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else if (i == 5 || i == 7)
        {
            _block.push_back(new Block(_image, PINK));                      // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ��������� ���
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i > 3 && i < 8)
        {
            _block.push_back(new Block(_image, PURPLE));              // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(67 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }        
    }

    // ����� ���
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6 )
        {
            _block.push_back(new Block(_image, YELLOW, true));                // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else if ((i > 3 && i < 6) || (i  > 6 && i < 9 ))
        {
            _block.push_back(new Block(_image, RED));                      // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    // ������ ���
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        
        _block.push_back(new Block(_image, ORANGE));                // ������� �������� �����
        _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
        _blk--;                                                         // C�������� �� ��������� �������.
        (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
    }

    // ������� ���
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            _block.push_back(new Block(_image, GREEN, true));               // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // C�������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));                     // ������� ������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
    }

    return 4;
}

// ������������� ��������� �������� ����

void Levels::GameInit()
{
    _platform->ChangePlatform(mediumPlatform);
    _platform->GetInstance()->ReSetBulltes();
    _platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    _flagBallMove = false;

    while (!_ball.empty())
    {
        _bl = _ball.begin();
        delete* _bl;
        _bl = _ball.erase(_bl);        
    }

    while (!_block.empty())
    {
        _blk = _block.begin();
        delete* _blk;
        _blk = _block.erase(_blk);
    }

    while (!_bonus.empty())
    {
        _bns = _bonus.begin();
        delete* _bns;
        _bns = _bonus.erase(_bns);
    }
    
    _ball.push_back(new Ball(_image));
    _bl = _ball.begin();
    (*_bl)->setPosition(BALL_START_POSITION);
}

void Levels::BallFall()
{
    if (Ball::GetBallCount() <= 1)
    {
        _flagBallMove = false;
        (*_bl)->SetFlagInit(true);
        _bl++;
        Menu::GetInstance().SetCountlives(-1);

        
    }
    else
    {
        delete* _bl;
        _bl = _ball.erase(_bl);
    }
}








