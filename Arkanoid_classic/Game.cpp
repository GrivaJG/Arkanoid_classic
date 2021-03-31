
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

//---------------------------------------------------------------------Инициализация стартовых значений игры

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
    // Инициализация случайного числа при помощи Вихря Мерсенна, нужен для того, чтобы при запуске шарика с платформы
    // Он полетел по случайной траектории
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double angleUnitCircleX = 0;         // Переменные в которых будет храниться направление движения шарика (вектор на единичной окружности)
    double angleUnitCircleY = 0;

    // Инициализируем переменную которая будет отдавать время и перезагружать его
    Clock clock;

    Clock clockForBullets;
    Clock clockForBallSpeed;
    _flagBallMove = false;

    while (window.isOpen())
    {
        // Блок обновления временной единицы 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float timeForBullet = clockForBullets.getElapsedTime().asMilliseconds();  // Заводим таймер для выпуска пуль      
        float timeForBallSpeed = clockForBallSpeed.getElapsedTime().asMilliseconds(); // Заводим таймер для ускорения шарика

        //---------------------------------------------Обработка событий нажатия кнопок
        Event event;
        while (window.pollEvent(event))
        {
            // Выключаем игру если нажата клавиша Esc или крестик в правом верхнем углу
            if (event.type == Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }


            // Реализуем событие однократного нажатия клавиши пробел
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                // Здесь отдадим команду начала игры через булеву переменную _flagBallMove;
                if (!_flagBallMove)
                {
                    // Формируем начальное направление движения шарика при помощи единичной окружности
                    angleUnitCircleX = (mersenne() % 150);
                    angleUnitCircleX = (angleUnitCircleX - 75) / 100;
                    angleUnitCircleY = sqrt(1.0 - pow(angleUnitCircleX, 2));
                    angleUnitCircleY = -1 * abs(angleUnitCircleY);

                    // Не заходим в этот блок до следующей инициализации
                    _flagBallMove = true;
                }

                // Если мы поймали бонус прилипания к платформе, то отлипаем от нее здесь
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


        //-------------------------------------------Создание дополнительных элементов

        // Если выбран бонус создания пуль, создаем пули
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


        //-------------------------------------------------Движение элементов

        // Движение платформы
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // Двигаемся влево, пока координата х не станет меньше 25,
            // Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            _platform->GetInstance()->Move(-0.5, time);
            if (_platform->GetInstance()->GetRect().left < BORDER_LEFT)
            {
                _platform->GetInstance()->setPosition(Vector2f(BORDER_LEFT, PLATFORM_START_POSITION.y));
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // Двигаемся влево, пока координата х не станет меньше 25,
            // Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            _platform->GetInstance()->Move(0.5, time);
            if (_platform->GetInstance()->GetRect().left + _platform->GetInstance()->GetRect().width > BORDER_RIGHT)
            {
                _platform->GetInstance()->setPosition(Vector2f(BORDER_RIGHT - _platform->GetInstance()->GetRect().width, PLATFORM_START_POSITION.y));
            }
        }


        // Если игра началась запускаем движение шарика
        if (_flagBallMove)
        {
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                (*_bl)->Move(angleUnitCircleX, angleUnitCircleY, time);
        }
        // Если игра не началась шарик привязан к платформе
        else
        {
            // Первое условие: "х" шарика всегда по середине платформы
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            {
                (*_bl)->setPosition((_platform->GetInstance()->GetRect().left +
                    (_platform->GetInstance()->GetRect().width / 2) - ((*_bl)->GetRect().width / 2)),
                    // Второе условие: "y" шарика всегда выше платформы на высоту шарика
                    _platform->GetInstance()->GetRect().top - (*_bl)->GetRect().height);
            }

        }

        // Двигаем бонусы
        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
        {
            (*_bns)->Move(time);
        }

        // Двигаем пули
        for (_blts = _bullets.begin(); _blts != _bullets.end(); _blts++)
        {
            (*_blts)->Move(time);
        }


        // --------------------------------------------------------------------После всех перемещений проверяем столкновения
        CollisionDetecter();


        // --------------------------------------------------------------------Если подошло время усложняем игру ускоряя шарик

        if (timeForBallSpeed > 10000)
        {
            clockForBallSpeed.restart();
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            {
                (*_bl)->SetSpeedFast();
            }
        }

        // -------------------------------------------Если жизни закончились выводим экран окончания игры, все переменные приводим к начальному значению
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

    Menu::GetInstance().CreateStartMenu(window);                        // Создаем стартовый экран
    Menu::GetInstance().PlayerInit();                                   // Начало игры, устанавливаем жизни игрока, и количество очков в начальные значения.

    _level++;
    while (_level <= 4 && window.isOpen())
    {
        window.clear();
        GameInit();                                                     // Приводим все элементы в стартовой полжожение                                                                        
        Menu::GetInstance().CreateLevelSplashScreen(window, _board, _level);
        InitLevel(_level);
        if (StartLevel(window) < 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, _block, _board, _platform);
            _level = 0;
            return 0;
        }
        _level++;                                                       // Увеличиваем уровень на 1
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