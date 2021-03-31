
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

Game::Game() : m_flag_ball_move(false), m_level(0)
{
    m_image.loadFromFile(IMGPATH);
    
    GameObjectInit();   //Game object initialization
}


void Game::StartGame()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    MusicAndSounds::GetInstance().BaseMusicPlay();

    // Random number for the zadaniya sluchainogo vectora dvigeniya
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double angleUnitCircleX = 0;         // Variables v kotorih budet hranitsya vector dlya sluchainogo poleta sharika pri pervom zapuske
    double angleUnitCircleY = 0;

    
    Clock clock;
    Clock clock_for_bullets;
    Clock clock_for_ball_speed;

    while (window.isOpen())
    {
        // Blok obnovleniya vremennoi edinici
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float timeForBullet    = clock_for_bullets.getElapsedTime().asMilliseconds();  // zavodim timer dlya vipuska bullets      
        float timeForBallSpeed = clock_for_ball_speed.getElapsedTime().asMilliseconds();  // zavodim timer dlya uskoreniya sharika

        //---------------------------------------------Obrabotka sobitii nagatiya klavish
        Event event;
        while (window.pollEvent(event))
        {
            // Esli nagat krestik v verhnem uglu ecrana or 
            if (event.type == Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }


            // –еализуем событие однократного нажати€ клавиши пробел
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                // «десь отдадим команду начала игры через булеву переменную _flagBallMove;
                if (!_flagBallMove)
                {
                    // ‘ормируем начальное направление движени€ шарика при помощи единичной окружности
                    angleUnitCircleX = (mersenne() % 150);
                    angleUnitCircleX = (angleUnitCircleX - 75) / 100;
                    angleUnitCircleY = sqrt(1.0 - pow(angleUnitCircleX, 2));
                    angleUnitCircleY = -1 * abs(angleUnitCircleY);

                    // Ќе заходим в этот блок до следующей инициализации
                    _flagBallMove = true;
                }

                // ≈сли мы поймали бонус прилипани€ к платформе, то отлипаем от нее здесь
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


        //-------------------------------------------—оздание дополнительных элементов

        // ≈сли выбран бонус создани€ пуль, создаем пули
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


        //-------------------------------------------------ƒвижение элементов

        // ƒвижение платформы
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // ƒвигаемс€ влево, пока координата х не станет меньше 25,
            // Ёто граница передвижени€, если пересекли то устанавливаем позицию в последнее возможное положение
            _platform->GetInstance()->Move(-0.5, time);
            if (_platform->GetInstance()->GetRect().left < BORDER_LEFT)
            {
                _platform->GetInstance()->setPosition(Vector2f(BORDER_LEFT, PLATFORM_START_POSITION.y));
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // ƒвигаемс€ влево, пока координата х не станет меньше 25,
            // Ёто граница передвижени€, если пересекли то устанавливаем позицию в последнее возможное положение
            _platform->GetInstance()->Move(0.5, time);
            if (_platform->GetInstance()->GetRect().left + _platform->GetInstance()->GetRect().width > BORDER_RIGHT)
            {
                _platform->GetInstance()->setPosition(Vector2f(BORDER_RIGHT - _platform->GetInstance()->GetRect().width, PLATFORM_START_POSITION.y));
            }
        }


        // ≈сли игра началась запускаем движение шарика
        if (_flagBallMove)
        {
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                (*_bl)->Move(angleUnitCircleX, angleUnitCircleY, time);
        }
        // ≈сли игра не началась шарик прив€зан к платформе
        else
        {
            // ѕервое условие: "х" шарика всегда по середине платформы
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            {
                (*_bl)->setPosition((_platform->GetInstance()->GetRect().left +
                    (_platform->GetInstance()->GetRect().width / 2) - ((*_bl)->GetRect().width / 2)),
                    // ¬торое условие: "y" шарика всегда выше платформы на высоту шарика
                    _platform->GetInstance()->GetRect().top - (*_bl)->GetRect().height);
            }

        }

        // ƒвигаем бонусы
        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
        {
            (*_bns)->Move(time);
        }

        // ƒвигаем пули
        for (_blts = _bullets.begin(); _blts != _bullets.end(); _blts++)
        {
            (*_blts)->Move(time);
        }


        // --------------------------------------------------------------------ѕосле всех перемещений провер€ем столкновени€
        CollisionDetecter();


        // --------------------------------------------------------------------≈сли подошло врем€ усложн€ем игру ускор€€ шарик

        if (timeForBallSpeed > 10000)
        {
            clockForBallSpeed.restart();
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            {
                (*_bl)->SetSpeedFast();
            }
        }

        // -------------------------------------------≈сли жизни закончились выводим экран окончани€ игры, все переменные приводим к начальному значению
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

}

//---------------------------------------------------------------------Initialization default values of the game objects

void Game::GameObjectInit()
{
    m_platform->ChangePlatform(mediumPlatform);
    m_platform->GetInstance()->ReSetBullets();
    m_platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    m_flag_ball_move = false;

    std::list<Ball*>::iterator bl;

    while (!m_balls.empty())
    {
        bl = m_balls.begin();
        delete* bl;
        bl = m_balls.erase(bl);
    }

    std::list<Block*>::iterator blk;

    while (!m_blocks.empty())
    {
        blk = m_blocks.begin();
        delete* blk;
        blk = m_blocks.erase(blk);
    }

    std::list<Bonus*>::iterator bns;
    while (!m_bonuses.empty())
    {
        bns = m_bonuses.begin();
        delete* bns;
        bns = m_bonuses.erase(bns);
    }

    m_balls.push_back(new Ball(m_image));
    bl = m_balls.begin();
    (*bl)->setPosition(BALL_START_POSITION);
}



void Game::GameLoop(RenderWindow& window)
{
   




int Levels::StartGame(RenderWindow& window)
{

    Menu::GetInstance().CreateStartMenu(window);                        // —оздаем стартовый экран
    Menu::GetInstance().PlayerInit();                                   // Ќачало игры, устанавливаем жизни игрока, и количество очков в начальные значени€.

    _level++;
    while (_level <= 4 && window.isOpen())
    {
        window.clear();
        GameInit();                                                     // ѕриводим все элементы в стартовой полжожение                                                                        
        Menu::GetInstance().CreateLevelSplashScreen(window, _board, _level);
        InitLevel(_level);
        if (StartLevel(window) < 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, _block, _board, _platform);
            _level = 0;
            return 0;
        }
        _level++;                                                       // ”величиваем уровень на 1
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