
#include "Levels.h"

//#include "Menu.h"

unsigned Ball::_ballCounter = 0;

Levels::Levels()
{
    _platform = new ConcretePlatform;
    _platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    _ball.push_back(new Ball(0.1));
    _bl = _ball.begin();
    (*_bl)->setPosition(BALL_START_POSITION);

    _level = 1;
    _changeLevel = true;
    _flagBallMove = false;

}



int Levels::StartGame(RenderWindow& window)
{
    //Menu::GetInstance().PlayerInit(); // ������ ����, ������������� ����� ������, ����� ������ � ���������� �����.
   
    //������������� ���������� ����� ��� ������ ����� ��������, ����� ��� ����, ����� ��� ������� ������ � ������ ����
    //�� ������� �� ��������� ����������
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double angleUnitCircleX = 0;         // ���������� � ������� ����� ��������� ����������� �������� ������ (������ �� ��������� ����������)
    double angleUnitCircleY = 0;         

    // �������������� ���������� ������� ����� �������� ����� � ������������� ���
    Clock clock;

    while (window.isOpen())
    {   
        // ���� ���������� ��������� ������� 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        // ��������� ������� ������� ������
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
                        _flagBallMove = true;;
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
        else
        {   //���� ���� �� ��������, ����� �������� � �������� ���������    
            // ������ �������: "�" ������ ������ �� �������� ���������
            _bl = _ball.begin();
            (*_bl)->setPosition((_platform->GetInstance()->GetRect().left +
                (_platform->GetInstance()->GetRect().width / 2) - ((*_bl)->GetRect().width / 2)),
                // ������ �������: "y" ������ ������ ���� ��������� �� ������ ������
                _platform->GetInstance()->GetRect().top - (*_bl)->GetRect().height);
        }

        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
        {
            (*_bns)->Move(time);
        }

        //����� ���� ����������� ��������� ������������
        CollisionDetecter();

        //if (Menu::GetInstance().GetCountlives() <= 0)
        //{
        //    Menu::GetInstance().SetScoreRecord();
        //    Menu::GetInstance().CreateStopGame(window, block, board);

        //    delete creatorPlatform;           
        //    return 0;
        //}

        if (_changeLevel) //���� ������ ��������� = true ���������� ������� ����� �������
        {
            _level = InitLevel(_level);
        //    Menu::GetInstance().Setlevel(level);
            _changeLevel = false;
        }

        window.clear();

        _board.CreateMap(window);
        _board.CreateMenu(window);

       /* Menu::GetInstance().CreateMenu(window); */

        for (_blk = _block.begin(); _blk != _block.end(); _blk++)
            window.draw(**_blk);

        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
            window.draw(**_bns);

        for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            window.draw(**_bl);
       
      
        window.draw(*_platform->GetInstance());
        
        

        window.display();


    }

    //delete creatorPlatform;
    return 0;
}

void Levels::CollisionDetecter()
{
//---------------------------------------------------------------------��������� ������������ ������ � ��������� �����

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
            (*_bl)->SetAngleUnitCircle(_platform->GetInstance()->CollisionWithBall(**_bl));
        }

        //----------------------------------------------------------------��������� ������������ ������ � �������, (������������ � ������)

        for (_blk = _block.begin(); _blk != _block.end();)
        {
            if ((*_blk)->GetRect().intersects((*_bl)->GetRect()))
            {
                (*_bl)->SetAngleUnitCircle((*_blk)->BallCollision(**_bl));
                if ((*_blk)->GetFlagBonus())
                {
                    _bonus.push_back(new Bonus((*_blk)->GetBlockType(), Vector2f((*_blk)->GetRect().left + (*_blk)->GetRect().width / 2 - BONUS_WIDTH / 2,
                        (*_blk)->getPosition().y)));
                }
                delete *_blk;
                _blk = _block.erase(_blk);
            }
            else
            {
                _blk++;
            }
        }


        // ���� ����� ���� (�� ���� ������ ����� ������� ��������� �������!!!)
        if ((*_bl)->getPosition().y > BORDER_BOTTOM)
        {
            if (Ball::GetBallCount() <= 1)
            {
                _flagBallMove = false;
                (*_bl)->SetFlagInit(true);
                _bl++;
            }
            else
            {
                delete* _bl;
                _bl = _ball.erase(_bl);
            }
            // Menu::GetInstance().SetCountlives(-1);
             
        }
        else
        {
            _bl++;
        }


    }
    

//-------------------------------------------------------------------��������� ������������ ������ � ���������� (������������ � ���������)
//---------------------------------------------------------------------------------------���� ����� ������ ������ ������� �����, �� ������� ���

    for (_bns = _bonus.begin(); _bns != _bonus.end();)
    {
        if ((*_bns)->GetRect().intersects(_platform->GetInstance()->GetRect()))
        {
            (*_bns)->CollisionWithPlatform(_ball);
            delete *_bns;
            _bns = _bonus.erase(_bns);
        }
        else if ((*_bns)->getPosition().y > BORDER_BOTTOM)
        {
            delete *_bns;
            _bns = _bonus.erase(_bns);
           
            
        }
        else
        {
            _bns++;
        }
        
    }





    
   
}


int Levels::InitLevel(int lvl)
{
    switch (lvl)
    {
    case 1:
        return CreateLevel1();
        break;
    case 2:
        return CreateLevel2();
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
            _block.push_back(new Block(YELLOW, true));  // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(YELLOW));
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
            _block.push_back(new Block(GREEN, true));  // ������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(GREEN));
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
            _block.push_back(new Block(PINK, true));  //������� �������� �����
            _blk = _block.end();                                            // �������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         // ��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // ������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(PINK));
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
            _block.push_back(new Block(PURPLE, true));                    //������� �������� �����
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(PURPLE));
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //����� ���
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 1 || i == 11)
        {
            _block.push_back(new Block(RED, true));  //������� �������� �����
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(RED));
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
            _block.push_back(new Block(BLUE, true));  //������� �������� �����
            _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--;                                                         //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            _block.push_back(new Block(BLUE));
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
        _block.push_back(new Block(ORANGE));
        _blk = _block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
        _blk--;                                                         //��������� �� ��������� �������.
        (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
       
    }
   
    return 2;
}

int Levels::CreateLevel2()
{
    int color = 1;
    int positionX;
    int positionY;
    for (int i = 0; i < 7; i++)
    {
        positionX = i;
        for (int j = 0; j < color; j++)
        {
            _block.push_back(new Block(GREEN));
            positionY = j;
            _blk = _block.end(); //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            _blk--; //��������� �� ��������� �������.
            (*_blk)->setPosition(40 + j * 55, 60 + i * 23);
        }
        color += 2;
    }

    return 3;
}








