#include "Levels.h"
#include "Menu.h"




int Levels::StartGame(RenderWindow& window, Platform& platform, Balls& ball, Border& board)
{
    Menu::GetInstance().PlayerInit();
    platform.setPosition(320, 550);
    ball.setPosition(376, 534);
    ball.SetSpeed(Vector2f(0.1, -0.1));

    bool startGame = true;
    //������������� ���������� ����� ��� ������ ����� ��������, ����� ��� ����, ����� ��� ������� ������ � ������ ����
    //�� ������� �� ��������� ����������
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double unit_circle_x = 0.0; //����������� �������� ������, � �� ��������� ����������
    double unit_circle_y = 0.0; //����������� �������� ������, y �� ��������� ����������

    //�������������� ���������� ������� ����� �������� ����� � ������������� ���
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            //��������� ���� ���� ������ ������� Esc ��� ������� � ������ ������� ����
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            //��������� ������� ������������ ������� ������� ������
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Space)
                {
                    //����� ������� ������� ������ ���� ����� ������ ���������� ballIsMove;
                    if (!ball.GetIsMove())
                    {
                        //��������� ��������� ����������� �������� ������ ��� ������ ��������� ����������
                        unit_circle_x = (mersenne() % 150);
                        unit_circle_x = (unit_circle_x - 75) / 100;
                        unit_circle_y = sqrt(1.0 - pow(unit_circle_x, 2));

                        //�� ������� � ���� ���� �� ��������� �������������
                        ball.SetIsMove(true);
                    }
                }
                if (event.key.code == Keyboard::X)
                {
                    ball.SetSpeedFast(50);
                }


                if (event.key.code == Keyboard::Z)
                {
                    ball.SetSpeedSlow(50);
                }

                if (event.key.code == Keyboard::F)
                    std::cout << "ball.GetSpeed().x = " << ball.GetSpeed().x << " ball.GetSpeed().y = " << ball.GetSpeed().y << std::endl;

            }
        }

        //�������� ���������
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            //��������� �����, ���� ���������� � �� ������ ������ 25,
            //��� ������� ������������, ���� ��������� �� ������������� ������� � ��������� ��������� ���������
            platform.move(-0.5 * time, 0);
            if (platform.getPosition().x < 25)
            {
                platform.setPosition(25, 550);
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            //��������� �����, ���� ���������� � �� ������ ������ 25,
            //��� ������� ������������, ���� ��������� �� ������������� ������� � ��������� ��������� ���������
            platform.move(0.5 * time, 0);
            if (platform.getPosition().x > platform.GetRightBorder())
            {
                platform.setPosition(platform.GetRightBorder(), 550);
            }
        }

        //���� ���� �������� ��������� �������� ������
        if (ball.GetIsMove())
        {
            ball.Move(unit_circle_x, unit_circle_y, time, &platform);
        }
        else
        {   //���� ���� �� ��������, ����� �������� � ��������� ��� ����� ������ � ���������
            ball.setPosition(platform.getPosition().x + ball.GetBallPositionOnPlatform(), 534);
        }

        if (Menu::GetInstance().GetCountlives() <= 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, platform, blocks, board);
            level = 1;
            change_level = true;
            return 0;
        }

        if (change_level) //���� ������ ��������� = true ���������� ������� ����� �������
        {
            level = InitLevel(level);
            Menu::GetInstance().Setlevel(level);
            change_level = false;
        }


        change_level = Block::Collision(blocks, blks, ball, bonuses, bns);

        Bonus::CollisionAndMove(bonuses, bns, platform, ball, time);

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        Menu::GetInstance().CreateMenu(window);

        for (blks = blocks.begin(); blks != blocks.end(); blks++)
            window.draw(**blks);

        for (bns = bonuses.begin(); bns != bonuses.end(); bns++)
            window.draw(**bns);

        window.draw(platform);
        window.draw(ball);

        window.display();


    }
    return 0;
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
            blocks.push_back(new Block(image, 594, 374, 54, 22, true, 6));  //������� �������� �����
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            blocks.push_back(new Block(image, 648, 22, 54, 22));
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������ ���
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            blocks.push_back(new Block(image, 648, 308, 54, 22, true, 1));  //������� �������� �����
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            blocks.push_back(new Block(image, 378, 22, 54, 22));
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������ ���
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 3 || i == 9)
        {
            blocks.push_back(new Block(image, 648, 330, 54, 22, true, 3));  //������� �������� �����
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            blocks.push_back(new Block(image, 486, 22, 54, 22));
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //��������� ���
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 2 || i == 10)
        {
            blocks.push_back(new Block(image, 594, 352, 54, 22, true, 4));  //������� �������� �����
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            blocks.push_back(new Block(image, 540, 22, 54, 22));
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //����� ���
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 1 || i == 11)
        {
            blocks.push_back(new Block(image, 648, 352, 54, 22, true, 5));  //������� �������� �����
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            blocks.push_back(new Block(image, 594, 22, 54, 22));
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }
    //������ ���
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            blocks.push_back(new Block(image, 594, 308, 54, 22, true, 0));  //������� �������� �����
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            blocks.push_back(new Block(image, 324, 22, 54, 22));
            blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--;                                                         //��������� �� ��������� �������.
            (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������� ���
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        blocks.push_back(new Block(image, 432, 22, 54, 22));
        blks = blocks.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
        blks--;                                                         //��������� �� ��������� �������.
        (*blks)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
       
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
            blocks.push_back(new Block(image, 324 + i * 54, 22, 54, 22));
            positionY = j;
            blks = blocks.end(); //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blks--; //��������� �� ��������� �������.
            (*blks)->setPosition(40 + j * 55, 60 + i * 23);
        }
        color += 2;
    }

    return 3;
}



