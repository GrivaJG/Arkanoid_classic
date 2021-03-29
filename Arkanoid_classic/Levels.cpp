
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "Config.h"
#include "Border.h"
#include "Block.h"
#include "Ball.h"
#include "Bonus.h"
#include "Bullets.h"
#include "Platform.h"

#include "MusicAndSounds.h"


#include "Levels.h"

unsigned Ball::_ballCounter = 0;

Levels::Levels(Image& img) : _image(img)
{
    
    _platform = new ConcretePlatform(_image);
    _platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    _ball.push_back(new Ball(_image));
    _bl = _ball.begin();
    (*_bl)->setPosition(BALL_START_POSITION);

    _level = 0;    
    _flagBallMove = false;

    MusicAndSounds::GetInstance();

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
    Menu::GetInstance().PlayerInit();                                   // ������ ����, ������������� ����� ������, � ���������� ����� � ��������� ��������.
   
    _level++;    
    while (_level <= 4 && window.isOpen())
    {
        window.clear();
        GameInit();                                                     // �������� ��� �������� � ��������� ����������                                                                        
        Menu::GetInstance().CreateLevelSplashScreen(window, _board, _level);
        InitLevel(_level);
        if (StartLevel(window) < 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, _block, _board, _platform);
            _level = 0;
            return 0;
        }
        _level++;                                                       // ����������� ������� �� 1
    }

    Menu::GetInstance().CreateEndGame(window, _block, _board, _platform);
    return 0;


    
}


int Levels::StartLevel(RenderWindow& window)
{
    // ������������� ���������� ����� ��� ������ ����� ��������, ����� ��� ����, ����� ��� ������� ������ � ���������
    // �� ������� �� ��������� ����������
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double angleUnitCircleX = 0;         // ���������� � ������� ����� ��������� ����������� �������� ������ (������ �� ��������� ����������)
    double angleUnitCircleY = 0;

    // �������������� ���������� ������� ����� �������� ����� � ������������� ���
    Clock clock;

    Clock clockForBullets;
    Clock clockForBallSpeed;
    _flagBallMove = false;

    while (window.isOpen())
    {
        // ���� ���������� ��������� ������� 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float timeForBullet = clockForBullets.getElapsedTime().asMilliseconds();  // ������� ������ ��� ������� ����      
        float timeForBallSpeed = clockForBallSpeed.getElapsedTime().asMilliseconds(); // ������� ������ ��� ��������� ������

        //---------------------------------------------��������� ������� ������� ������
        Event event;
        while (window.pollEvent(event))
        {
            // ��������� ���� ���� ������ ������� Esc ��� ������� � ������ ������� ����
            if (event.type == Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
                

            // ��������� ������� ������������ ������� ������� ������
            if (Keyboard::isKeyPressed(Keyboard::Space))
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
                
                // ���� �� ������� ����� ���������� � ���������, �� �������� �� ��� �����
                for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                {
                    if ((*_bl)->getPosition().y == _platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT + 1)
                    {
                        (*_bl)->SetFlagCatch(false);
                        (*_bl)->SetFlagBallCatchPosition(false);
                    }
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

                MusicAndSounds::GetInstance().PlatformFirePlay();

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
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            {
                (*_bl)->setPosition((_platform->GetInstance()->GetRect().left +
                    (_platform->GetInstance()->GetRect().width / 2) - ((*_bl)->GetRect().width / 2)),
                    // ������ �������: "y" ������ ������ ���� ��������� �� ������ ������
                    _platform->GetInstance()->GetRect().top - (*_bl)->GetRect().height);
            }

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


        // --------------------------------------------------------------------����� ���� ����������� ��������� ������������
        CollisionDetecter();


        // --------------------------------------------------------------------���� ������� ����� ��������� ���� ������� �����

        if (timeForBallSpeed > 10000)
        {
            clockForBallSpeed.restart();
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            {
                (*_bl)->SetSpeedFast();
            }
        }

        // -------------------------------------------���� ����� ����������� ������� ����� ��������� ����, ��� ���������� �������� � ���������� ��������
        if (Menu::GetInstance().GetCountlives() <= 0)
        {
            return -1;
        }

        if (_block.empty())
        {
            return 0;            
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
}

//----------------------------------------------------------------�������� �������

int Levels::InitLevel(int lvl)
{
    std::ifstream file("Config/lvlCreator.ini");
    if (file.is_open())
        std::cout << "FILE is open" << std::endl;

    std::ostringstream level;
    level << lvl;
    std::string levelForCreate = "Level: " + level.str();
    
    std::string stringOfFile;

    while (!file.eof())
    {
        std::getline(file, stringOfFile);
        if (stringOfFile == levelForCreate)
        {
            int positionX = 0;
            int positionY = 0;
            int startPositionTop = 0;
            int startPositionLeft = 0;

            std::getline(file, stringOfFile);

            std::stringstream pos;

            for (size_t i = 14; i < stringOfFile.length(); i++)
            {
                pos << stringOfFile[i];
            }

            pos >> startPositionTop;

            while (stringOfFile != "\0" && !file.eof())
            {

                std::getline(file, stringOfFile);
                std::stringstream ss(stringOfFile);
               
                ss >> startPositionLeft;
                
                for (size_t i = 0; i < stringOfFile.length(); i++)
                {
                    if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'Y' && stringOfFile[i + 2] == 'E')
                    {
                        _block.push_back(new Block(_image, YELLOW, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'G' && stringOfFile[i + 2] == 'R')
                    {
                        _block.push_back(new Block(_image, GREEN, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'P' && stringOfFile[i + 2] == 'I')
                    {
                        _block.push_back(new Block(_image, PINK, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'P' && stringOfFile[i + 2] == 'U')
                    {
                        _block.push_back(new Block(_image, PURPLE, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'R' && stringOfFile[i + 2] == 'E')
                    {
                        _block.push_back(new Block(_image, RED, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'B' && stringOfFile[i + 2] == 'L')
                    {
                        _block.push_back(new Block(_image, BLUE, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'Y' && stringOfFile[i + 1] == 'E')
                    {
                        _block.push_back(new Block(_image, YELLOW));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'G' && stringOfFile[i + 1] == 'R')
                    {
                        _block.push_back(new Block(_image, GREEN));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'P' && stringOfFile[i + 1] == 'I')
                    {
                        _block.push_back(new Block(_image, PINK));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'P' && stringOfFile[i + 1] == 'U')
                    {
                        _block.push_back(new Block(_image, PURPLE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'R' && stringOfFile[i + 1] == 'E')
                    {
                        _block.push_back(new Block(_image, RED));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'L')
                    {
                        _block.push_back(new Block(_image, BLUE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'O' && stringOfFile[i + 1] == 'R')
                    {
                        _block.push_back(new Block(_image, ORANGE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;                        
                    }

                    else if (stringOfFile[i] == 'N' && stringOfFile[i + 1] == 'B')
                    {  
                        positionX++;
                        i += 2;
                    }
                   
                }
                
                positionX = 0;
                positionY++;
                
            }
        }
            
    }
    

    file.close();
    return 0;
}

int Levels::BlockSetPosition(int startPositionTop, int startPositionLeft, int positionX, int positionY)
{
    _blk = _block.end();
    _blk--;
    (*_blk)->setPosition(startPositionLeft + positionX * (BLOCK_WIDTH + 1), startPositionTop + positionY * (BLOCK_HEIGHT + 1));
    positionX++;
    return positionX;
}



//---------------------------------------------------------------------������������� ��������� �������� ����

void Levels::GameInit()
{   
    _platform->ChangePlatform(mediumPlatform);
    _platform->GetInstance()->ReSetBullets();
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


//-------------------------------------------------------------------������� ������
void Levels::BallFall()
{
    if (Ball::GetBallCount() <= 1)
    {
        _flagBallMove = false;
        (*_bl)->SetFlagInit(true); 
        (*_bl)->ResetCatch();
        (*_bl)->ResetSpeed();
        _bl++;

        Menu::GetInstance().SetCountlives(-1);
        MusicAndSounds::GetInstance().BallFallPlay();
        
        _platform->GetInstance()->ReSetBullets();
        _platform->ChangePlatform(mediumPlatform);

        
    }
    else
    {
        delete* _bl;
        _bl = _ball.erase(_bl);
        MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
    }
}








