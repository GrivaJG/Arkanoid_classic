
#include "Config.h"
#include "Border.h"
#include "Block.h"
#include "Ball.h"
#include "Bonus.h"
#include "Platform.h"
#include "Bullets.h"
#include "MusicAndSounds.h"
#include "Game.h"


unsigned Ball::_ballCounter = 0;

Game::Game() : _flagBallMove(false), _level(0)
{
    m_image.loadFromFile(IMGPATH);
    
}


void Game::StartGame()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    MusicAndSounds::GetInstance().BaseMusicPlay();
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