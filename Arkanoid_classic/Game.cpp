
#include "Block.h"
#include "Ball.h"
#include "Bonus.h"
#include "Bullets.h"
#include "MusicAndSounds.h"

#include "CollisionManager.h"
#include "Levels.h"
#include "Menu.h"

#include "Game.h"

uint16_t Ball::m_ball_counter = 0;

Game::Game() : m_levels(m_image), m_flag_ball_move(false), m_level(0)
{
    m_image.loadFromFile(IMGPATH);
    
    m_platform = new ConcretePlatform(m_image);
    assert(m_platform);
    m_collision_manager = new CollisionManager(m_platform, m_balls, m_blocks, m_bonuses, m_bullets);
    assert(m_collision_manager);

    GameObjectInit();   //Game object initialization    
}

void Game::StartGame()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    MusicAndSounds::GetInstance().BaseMusicPlay();

    Menu::GetInstance().CreateStartMenu(window);                        // Startoviy ecran pered zapuskom igrvogo processa
    Menu::GetInstance().PlayerInit();                                   // Pered nachalom igri ustanavlivaem ochki i gizni v startovie znacheniya

    m_level++;
    while (m_level <= 4 && window.isOpen())                             //Kostil
    {
        window.clear();        
        GameObjectInit();                                               // Privodim vse igrovie elementi v startovoe pologenie
        Menu::GetInstance().CreateLevelSplashScreen(window, m_board, m_level);
        m_levels.InitLevel(m_level, m_blocks);
        if (GameLoop(window) > 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, m_blocks, m_board, m_platform);
            Menu::GetInstance().PlayerInit();
            m_level = 0;            
        }
        m_level++;                                                       
    }

    Menu::GetInstance().CreateEndGame(window, m_blocks, m_board, m_platform);
}


uint8_t Game::GameLoop(RenderWindow& window)
{  
    // Random number for zadaniya sluchainogo vectora dvigeniya sharika
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double angle_unit_circleX = 0;         // Peremennie v kotorih budet hranitsya vector dlya sluchainogo poleta sharika pri pervom zapuske
    double angle_unit_circleY = 0;

    
    Clock clock;
    Clock clock_for_bullets;
    Clock clock_for_ball_speed;

    std::vector<Block*>::iterator blk;
    std::vector<Bonus*>::iterator bns;
    std::vector<Ball*>::iterator bl;
    std::vector<Bullets*>::iterator blts;    

    while (window.isOpen())
    {
        // Blok obnovleniya vremennoi edinici
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float time_for_bullet    = clock_for_bullets.getElapsedTime().asMilliseconds();  // zavodim timer dlya vipuska bullets      
        float time_for_ball_speed = clock_for_ball_speed.getElapsedTime().asMilliseconds();  // zavodim timer dlya uskoreniya sharika

        //---------------------------------------------Obrabotka sobitii nagatiya klavish
        Event event;
        while (window.pollEvent(event))
        {            
            if (event.type == Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }           
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                // start game procees if m_flag_ball_move = false and key presed space;
                if (!m_flag_ball_move)
                {
                    // Formiruem nachalnoe napravlenie dvigeniya sharika pri pomoschi edinichnoi okrugnostyi
                    angle_unit_circleX = (mersenne() % 150);
                    angle_unit_circleX = (angle_unit_circleX - 75) / 100;
                    angle_unit_circleY = sqrt(1.0 - pow(angle_unit_circleX, 2));
                    angle_unit_circleY = -1 * abs(angle_unit_circleY);

                    // Ne zahodim v etot blok do sleduuschei initializacii
                    m_flag_ball_move = true;
                }

                std::vector<Ball*>::iterator bl;
                // Esli poimali bonus prilipaniya to otlipaem on nee zdes
                for (bl = m_balls.begin(); bl != m_balls.end(); bl++)
                {
                    if ((*bl)->getPosition().y == m_platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT + 1)
                    {
                        (*bl)->SetFlagCatch(false);
                        (*bl)->SetFlagBallCatchPosition(false);
                    }
                }

            }
        }
        //-------------------------------------------Create additional elements

        // Esli poluchen bonus sozdaniya bullets to sozdaem bullets
        if (m_platform->GetInstance()->GetBullets() > 0)
        {
            if (time_for_bullet > 1000)
            {
                m_platform->GetInstance()->Fire();

                MusicAndSounds::GetInstance().PlatformFirePlay();

                clock_for_bullets.restart();

                Bullets* temp_bullet1 = new Bullets(m_image);
                Bullets* temp_bullet2 = new Bullets(m_image);

                temp_bullet1->setPosition(m_platform->GetInstance()->GetRect().left, m_platform->GetInstance()->GetRect().top +
                    m_platform->GetInstance()->GetRect().height / 2 - BULLET_HEIGHT / 2);

                temp_bullet2->setPosition(m_platform->GetInstance()->GetRect().left + m_platform->GetInstance()->GetRect().width - BULLET_WIDTH,
                    m_platform->GetInstance()->GetRect().top + m_platform->GetInstance()->GetRect().height / 2 - BULLET_HEIGHT / 2);

                m_bullets.push_back(temp_bullet1);
                m_bullets.push_back(temp_bullet2);

            }
        }
        //-------------------------------------------------Moving elements

        // Moving Platform
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // Dvigaemsya vlevo poka koordinata x ne stanet menshe BORDER_LEFT            
            m_platform->GetInstance()->Move(-0.5, time);
            if (m_platform->GetInstance()->GetRect().left < BORDER_LEFT)
            {
                m_platform->GetInstance()->setPosition(Vector2f(BORDER_LEFT, PLATFORM_START_POSITION.y));
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // Dvigaemsya vlevo poka koordinata x ne stanet bolshe BORDER_RIGHT             
            m_platform->GetInstance()->Move(0.5, time);
            if (m_platform->GetInstance()->GetRect().left + m_platform->GetInstance()->GetRect().width > BORDER_RIGHT)
            {
                m_platform->GetInstance()->setPosition(Vector2f(BORDER_RIGHT - m_platform->GetInstance()->GetRect().width, PLATFORM_START_POSITION.y));
            }
        }

        // zapuskaem dvigenie sharika
        if (m_flag_ball_move)
        {
            for (bl = m_balls.begin(); bl != m_balls.end(); bl++)
                (*bl)->Move(angle_unit_circleX, angle_unit_circleY, time);
        }
        // Esli igra ne nachalas - sharik privyazan k platforme
        else
        {
            // First condition: "õ" sharika vsegda privyazan k seredine platformi
            for (bl = m_balls.begin(); bl != m_balls.end(); bl++)
            {
                (*bl)->setPosition((m_platform->GetInstance()->GetRect().left +
                    (m_platform->GetInstance()->GetRect().width / 2) - ((*bl)->GetRect().width / 2)),
                    // Second condition: "y" sharika vsegda vishe platformi
                    m_platform->GetInstance()->GetRect().top - (*bl)->GetRect().height);
            }
        }

        // Moving bonus
        std::vector<Bonus*>::iterator bns;
        for (bns = m_bonuses.begin(); bns != m_bonuses.end(); bns++)
        {
            (*bns)->Move(time);
        }

        // Moving bullets
        std::vector<Bullets*>::iterator blts;
        for (blts = m_bullets.begin(); blts != m_bullets.end(); blts++)
        {
            (*blts)->Move(time);
        }

        // --------------------------------------------------------------------Posle vseh peremesheniy proveryaem stolknoveniya
        m_collision_manager->CollisionDetecter();

        // --------------------------------------------------------------------Uskoryaem sharik cherez vremennie intervali (kostil)
        if (time_for_ball_speed > 10000)
        {
            clock_for_ball_speed.restart();
            for (bl = m_balls.begin(); bl != m_balls.end(); bl++)
            {
                (*bl)->SetSpeedFast();
            }
        }
        // -------------------------------------------Proveryaem kolichestvo gizney i esly oni zakonchilis - zakanchivaem igru
        if (Menu::GetInstance().GetCountlives() <= 0)
        {
            return 1;
        }

        if (m_blocks.empty())
        {
            return 0;
        }

        window.clear();

        m_board.CreateMap(window);
        m_board.CreateMenu(window);

        Menu::GetInstance().CreateMenu(window, m_level);

        for (blk = m_blocks.begin(); blk != m_blocks.end(); blk++)
            window.draw(**blk);

        for (bns = m_bonuses.begin(); bns != m_bonuses.end(); bns++)
            window.draw(**bns);

        for (bl = m_balls.begin(); bl != m_balls.end(); bl++)
            window.draw(**bl);

        for (blts = m_bullets.begin(); blts != m_bullets.end(); blts++)
        {
            window.draw(**blts);
        }

        window.draw(*m_platform->GetInstance());

        window.display();
    }
    return 0;
}

//---------------------------------------------------------------------Initialization default values of the game objects
void Game::GameObjectInit()
{
    m_platform->ChangePlatform(mediumPlatform);
    m_platform->GetInstance()->ReSetBullets();
    m_platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    m_flag_ball_move = false;

    std::vector<Ball*>::iterator bl;

    while (!m_balls.empty())
    {
        bl = m_balls.begin();
        delete* bl;
        bl = m_balls.erase(bl);
    }

    std::vector<Block*>::iterator blk;

    while (!m_blocks.empty())
    {
        blk = m_blocks.begin();
        delete* blk;
        blk = m_blocks.erase(blk);
    }

    std::vector<Bonus*>::iterator bns;
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

Game::~Game()
{
    delete m_platform;

    std::vector<Block*>::iterator blk;
    std::vector<Bonus*>::iterator bns;
    std::vector<Ball*>::iterator bl;
    std::vector<Bullets*>::iterator blts;

    while (!m_blocks.empty())
    {
        blk = m_blocks.begin();
        delete* blk;
        blk = m_blocks.erase(blk);
    }

    while (!m_bonuses.empty())
    {
        bns = m_bonuses.begin();
        delete* bns;
        bns = m_bonuses.erase(bns);
    }

    while (!m_balls.empty())
    {
        bl = m_balls.begin();
        delete* bl;
        bl = m_balls.erase(bl);
    }

    while (!m_bullets.empty())
    {
        blts = m_bullets.begin();
        delete* blts;
        blts = m_bullets.erase(blts);
    }
}