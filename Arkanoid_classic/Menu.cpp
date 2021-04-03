
#include "Block.h"
#include "Ball.h"
#include "Menu.h"

Menu::Menu()
{
    if (m_font.loadFromFile(FONTPATH) == NULL)
        std::cout << "Font Error" << std::endl;

     m_text_start_game.setFont(m_font);
     m_text_start_game.setCharacterSize(55);
     m_text_start_game.setColor(Color::Red);
     m_text_start_game.setStyle(Text::Bold);

     m_text_stop_game.setFont(m_font);
     m_text_stop_game.setCharacterSize(55);
     m_text_stop_game.setColor(Color::Red);
     m_text_stop_game.setStyle(Text::Bold);

     m_text_score.setFont(m_font);
     m_text_score.setCharacterSize(35);
     m_text_score.setColor(Color::Yellow);
     m_text_score.setStyle(Text::Bold);
     m_text_score.setPosition(850, 40);


     m_text_level.setFont(m_font);
     m_text_level.setCharacterSize(35);
     m_text_level.setColor(Color::Yellow);
     m_text_level.setStyle(Text::Bold);
     m_text_level.setPosition(850, 200);


     m_text_lives.setFont(m_font);
     m_text_lives.setCharacterSize(35);
     m_text_lives.setColor(Color::Yellow);
     m_text_lives.setStyle(Text::Bold);
     m_text_lives.setPosition(850, 120);


     m_text_congratulations.setFont(m_font);
     m_text_congratulations.setCharacterSize(35);
     m_text_congratulations.setColor(Color::Yellow);
     m_text_congratulations.setStyle(Text::Bold);


}

void Menu::CreateStartMenu(RenderWindow& window)
{
    Image image;
    image.loadFromFile(IMGPATH);
    Texture texture;
    texture.loadFromImage(image);

    Sprite blue_bonus;
    blue_bonus.setTexture(texture);
    blue_bonus.setTextureRect(IntRect(456, 449, 27, 30));
    blue_bonus.setPosition(100, 200);

    Sprite print_platform_large;
    print_platform_large.setTexture(texture);
    print_platform_large.setTextureRect(IntRect(148, 302, 128, 31));
    print_platform_large.setPosition(190, 200);

    Sprite  print_platform_small;
    print_platform_small.setTexture(texture);
    print_platform_small.setTextureRect(IntRect(0, 302, 58, 31));
    print_platform_small.setPosition(378, 200);

    Sprite print_ball;
    print_ball.setTexture(texture);
    print_ball.setTextureRect(IntRect(64, 128, 16, 16));
    print_ball.setPosition(190, 353);

    Sprite green_bonus;
    green_bonus.setTexture(texture);
    green_bonus.setTextureRect(IntRect(488, 449, 27, 30));
    green_bonus.setPosition(100, 250);

    Sprite pink_bonus;
    pink_bonus.setTexture(texture);
    pink_bonus.setTextureRect(IntRect(520, 449, 27, 30));
    pink_bonus.setPosition(100, 300);

    Sprite purple_bonus;
    purple_bonus.setTexture(texture);
    purple_bonus.setTextureRect(IntRect(553, 449, 27, 30));
    purple_bonus.setPosition(100, 350);

    Sprite red_bonus;
    red_bonus.setTexture(texture);
    red_bonus.setTextureRect(IntRect(456, 482, 27, 30));
    red_bonus.setPosition(100, 400);

    Sprite yellow_bonus;
    yellow_bonus.setTexture(texture);
    yellow_bonus.setTextureRect(IntRect(488, 481, 27, 30));
    yellow_bonus.setPosition(100, 450);

    Text text_equal("=", m_font, 25);
    text_equal.setColor(Color::Red);
    text_equal.setStyle(Text::Bold);

    Text text_or("or", m_font, 25);
    text_or.setColor(Color::Red);
    text_or.setStyle(Text::Bold);
    text_or.setPosition(338, 200);

    Text text_laser_on_board("Laser on board", m_font, 25);
    text_laser_on_board.setColor(Color::Red);
    text_laser_on_board.setStyle(Text::Bold);
    text_laser_on_board.setPosition(190, 396);

    Text text_platform_catch_ball("Platform catch ball", m_font, 25);
    text_platform_catch_ball.setColor(Color::Red);
    text_platform_catch_ball.setStyle(Text::Bold);
    text_platform_catch_ball.setPosition(190, 246);

    Text text_slow_or_fast_ball("Slow or Fast ball speed", m_font, 25);
    text_slow_or_fast_ball.setColor(Color::Red);
    text_slow_or_fast_ball.setStyle(Text::Bold);
    text_slow_or_fast_ball.setPosition(190, 296);

    Text text_extra_life("Extra Life", m_font, 25);
    text_extra_life.setColor(Color::Red);
    text_extra_life.setStyle(Text::Bold);
    text_extra_life.setPosition(190, 446);

    Text text_multiply("X 3", m_font, 25);
    text_multiply.setColor(Color::Red);
    text_multiply.setStyle(Text::Bold);
    text_multiply.setPosition(216, 344);

    MediumPlatform platform(image);
    Ball ball(image);
    Border board;

    platform.setPosition(-25, 550);
    ball.setPosition(800, 534);
    m_text_start_game.setString("PRESS ENTER TO START");
    m_text_start_game.setPosition(120, 0);

    auto& score = Menu::GetInstance().GetCountScore();
    auto& lives = Menu::GetInstance().GetCountlives();

    Clock clock;

    bool is_menu = true;
    while (is_menu)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        sf::Event event;
        while (window.pollEvent(event))
        {            
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
                is_menu = false;
            }
            
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    is_menu = false;
                }
            }
        }

        if (platform.getPosition().x < 320)
            platform.move(time * 0.5, 0);
        else
            platform.setPosition(320, 550);

        if (ball.getPosition().x > platform.getPosition().x + 37)
            ball.move(time * -0.5, 0);
        else
            ball.setPosition(platform.getPosition().x + 37, platform.getPosition().y - 16);

        if (m_text_start_game.getPosition().y <= 80)
            m_text_start_game.move(0, time * 0.2);


        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        m_text_score.setString("Score");

        m_text_lives.setString("Lives");

        m_text_level.setString("Round");

        for (int i = 0; i < 6; i++)
        {
            text_equal.setPosition(150, 196 + i * 50);
            window.draw(text_equal);
        }


        window.draw(text_multiply);
        window.draw(print_ball);
        window.draw(text_slow_or_fast_ball);
        window.draw(text_platform_catch_ball);
        window.draw(text_laser_on_board);
        window.draw(text_or);
        window.draw(print_platform_small);
        window.draw(print_platform_large);
        window.draw(text_extra_life);
        window.draw(green_bonus);
        window.draw(blue_bonus);
        window.draw(pink_bonus);
        window.draw(purple_bonus);
        window.draw(red_bonus);
        window.draw(yellow_bonus);

        window.draw(platform);
        window.draw(ball);
        window.draw(m_text_score);
        window.draw(m_text_lives);
        window.draw(m_text_level);
        window.draw(m_text_start_game);

        window.display();
    }
}

void Menu::CreateMenu(RenderWindow& window, unsigned level)
{
    std::ostringstream player_score;
    std::ostringstream player_lives;
    std::ostringstream game_level;

    player_score << m_score;
    player_lives << m_lives;
    game_level << level;

    m_text_score.setString("Score: " + player_score.str());
    m_text_lives.setString("Lives: " + player_lives.str());
    m_text_level.setString("Level: " + game_level.str());

    window.draw(m_text_score);
    window.draw(m_text_lives);
    window.draw(m_text_level);
}

void Menu::CreateStopGame(RenderWindow& window, std::vector<Block*>& blocks, Border& board, ConcretePlatform* platform)
{
    std::ostringstream record;
    record << m_score_record;
    m_text_stop_game.setString("Game Over\n\nYour Record is: " + record.str() + "\n\n" +
        "Press Enter to try again");
    m_text_stop_game.setPosition(100, -50);

    std::vector<Block*>::iterator blks;

    Clock clock;

    bool is_menu = true;
    while (is_menu)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        sf::Event event;
        while (window.pollEvent(event))
        {            
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
                is_menu = false;
            }
           
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    is_menu = false;
                }
            }
        }

        if (platform->GetInstance()->getPosition().x < 1300)
            platform->GetInstance()->move(time * 1.5, 0);
        else
            platform->GetInstance()->setPosition(1300, 550);


        for (blks = blocks.begin(); blks != blocks.end();)
        {
            if ((*blks)->getPosition().x > -50)
            {
                (*blks)->move(time * -1.5, 0);
                blks++;
            }
            else
            {
                delete (*blks);
                blks = blocks.erase(blks);
            }

        }


        if (m_text_stop_game.getPosition().y < 100)
            m_text_stop_game.move(0, time * 0.5);
        else
            m_text_stop_game.setPosition(m_text_stop_game.getPosition().x, 100);



        m_text_score.setString("Score");
        m_text_score.setString("Lives");
        m_text_score.setString("Round");

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        for (blks = blocks.begin(); blks != blocks.end(); blks++)
            window.draw(**blks);

        window.draw(*platform->GetInstance());
        window.draw(m_text_score);
        window.draw(m_text_lives);
        window.draw(m_text_level);
        window.draw(m_text_stop_game);

        window.display();
    }
}

void Menu::CreateEndGame(RenderWindow& window, std::vector<Block*>& blocks, Border& board, ConcretePlatform* platform)
{
    std::ostringstream record;
    record << m_score_record;
    std::ostringstream score;
    score << m_score;

    m_text_congratulations.setString("Congratulations\n\nYou Score is: " + score.str() + "\n\nYour Record is: " + record.str() + "\n\n" +
        "Press Enter to try again");
    m_text_congratulations.setPosition(100, -50);

    std::vector<Block*>::iterator blks;

    Clock clock;

    bool is_menu = true;
    while (is_menu && window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        sf::Event event;
        while (window.pollEvent(event))
        {            
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
                is_menu = false;
            }            
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    is_menu = false;
                }
            }
        }
        if (platform->GetInstance()->getPosition().x < 1300)
            platform->GetInstance()->move(time * 1.5, 0);
        else
            platform->GetInstance()->setPosition(1300, 550);

        for (blks = blocks.begin(); blks != blocks.end();)
        {
            if ((*blks)->getPosition().x > -50)
            {
                (*blks)->move(time * -1.5, 0);
                blks++;
            }
            else
            {
                delete (*blks);
                blks = blocks.erase(blks);
            }

        }


        if (m_text_stop_game.getPosition().y < 100)
            m_text_stop_game.move(0, time * 0.5);
        else
            m_text_stop_game.setPosition(m_text_stop_game.getPosition().x, 100);



        m_text_score.setString("Score");
        m_text_lives.setString("Lives");
        m_text_level.setString("Round");

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        for (blks = blocks.begin(); blks != blocks.end(); blks++)
            window.draw(**blks);

        window.draw(*platform->GetInstance());
        window.draw(m_text_score);
        window.draw(m_text_lives);
        window.draw(m_text_level);
        window.draw(m_text_stop_game);

        window.display();
    }
}

void Menu::CreateLevelSplashScreen(RenderWindow& window, Border& board, unsigned level)
{
    bool is_open = true;

    Text text_splash_screen_level("Level ", m_font, 60);
    text_splash_screen_level.setColor(Color::Yellow);
    text_splash_screen_level.setStyle(Text::Bold);
    text_splash_screen_level.setPosition(300, 250);

    std::ostringstream game_level;
    game_level << level;

    Clock clock;

    Clock clock_is_open;

    while (is_open && window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float time_is_open = clock_is_open.getElapsedTime().asMilliseconds();

        if (time_is_open > 3000)
        {
            is_open = false;
            window.clear();
        }

        text_splash_screen_level.setString("Level " + game_level.str());

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        window.draw(text_splash_screen_level);

        window.display();

    }

}