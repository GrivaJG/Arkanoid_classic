
#include "Levels.h"



int Levels::StartGame(RenderWindow& window)
{
    Menu::GetInstance().PlayerInit(); // ������ ����, ������������� ����� ������, ����� ������ � ���������� �����.
    
    Border board;
    
    CreatorPlatform* creatorPlatform = new CreatorMediumPlatform(); // ����� ������� ������� ������� ���������
    creatorPlatform->SomeSetPosition(PLATFORM_START_POSITION);      // ������������� ��������� �������
    
    // ������� �����
    Ball ball(0.1);
    ball.setPosition(BALL_START_POSITION);
    
   
    //������������� ���������� ����� ��� ������ ����� ��������, ����� ��� ����, ����� ��� ������� ������ � ������ ����
    //�� ������� �� ��������� ����������
    std::random_device rd;
    std::mt19937 mersenne(rd());

    Vector2f angleUnitCircle; // ���������� � ������� ����� ��������� ����������� �������� ������ (������ �� ��������� ����������)

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
                    //����� ������� ������� ������ ���� ����� ������ ���������� ballIsMove;
                    if (!ball.GetFlagMove())
                    {
                        //��������� ��������� ����������� �������� ������ ��� ������ ��������� ����������
                        angleUnitCircle.x = ((mersenne() % 150) - 75) / 100;                        
                        angleUnitCircle.y = sqrt(1.0 - pow(angleUnitCircle.x, 2));

                        //�� ������� � ���� ���� �� ��������� �������������
                        ball.SetFlagMove(true);
                    }
                }
                if (event.key.code == Keyboard::X)
                {
                    ball.SetSpeedFast();
                }


                if (event.key.code == Keyboard::Z)
                {
                    ball.SetSpeedSlow();
                }
            }
        }

        //�������� ���������
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            //��������� �����, ���� ���������� � �� ������ ������ 25,
            //��� ������� ������������, ���� ��������� �� ������������� ������� � ��������� ��������� ���������
            creatorPlatform->SomeMove(-0.5, time);
            if (creatorPlatform->SomeGetRect().left < BORDER_LEFT)
            {   
                creatorPlatform->SomeSetPosition(Vector2f(BORDER_LEFT, PLATFORM_START_POSITION.y));
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            //��������� �����, ���� ���������� � �� ������ ������ 25,
            //��� ������� ������������, ���� ��������� �� ������������� ������� � ��������� ��������� ���������
            creatorPlatform->SomeMove(-0.5, time);
            if (creatorPlatform->SomeGetRect().left+ creatorPlatform->SomeGetRect().left > BORDER_RIGHT)
            {
                creatorPlatform->SomeSetPosition(Vector2f(BORDER_RIGHT-creatorPlatform->SomeGetRect().width, PLATFORM_START_POSITION.y));
            }
        }

        //���� ���� �������� ��������� �������� ������
        if (ball.GetFlagMove())
        {
            ball.Move(angleUnitCircle, time, creatorPlatform);
        }
        else
        {   //���� ���� �� ��������, ����� �������� � �������� ��������� 
            ball.setPosition((creatorPlatform->SomeGetRect().left + (creatorPlatform->SomeGetRect().width/2)-(ball.GetRect().width/2)),
                creatorPlatform->SomeGetRect().top - ball.GetRect().height);
        }

        if (Menu::GetInstance().GetCountlives() <= 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, block, board);

            delete creatorPlatform;           
            return 0;
        }

        if (change_level) //���� ������ ��������� = true ���������� ������� ����� �������
        {
            level = InitLevel(level);
            Menu::GetInstance().Setlevel(level);
            change_level = false;
        }

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        Menu::GetInstance().CreateMenu(window);

        for (blk = block.begin(); blk != block.end(); blk++)
            window.draw(**blk);

        for (bns = bonus.begin(); bns != bonus.end(); bns++)
            window.draw(**bns);

        creatorPlatform->SomeDraw(window);

        
        window.draw(ball);

        window.display();


    }

    delete creatorPlatform;
    return 0;
}


void Levels::CreateBonus(FloatRect blockPosition, BlockType blockType)
{

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
            block.push_back(new Block(YELLOW, true));  //������� �������� �����
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            block.push_back(new Block(YELLOW));
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������ ���
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            block.push_back(new Block(GREEN, true));  //������� �������� �����
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            block.push_back(new Block(GREEN));
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������ ���
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 3 || i == 9)
        {
            block.push_back(new Block(PINK, true));  //������� �������� �����
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            block.push_back(new Block(PINK));
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //��������� ���
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 2 || i == 10)
        {
            block.push_back(new Block(PURPLE, true));                    //������� �������� �����
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            block.push_back(new Block(PURPLE));
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //����� ���
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 1 || i == 11)
        {
            block.push_back(new Block(RED, true));  //������� �������� �����
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            block.push_back(new Block(RED));
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }
    //������ ���
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            block.push_back(new Block(BLUE, true));  //������� �������� �����
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
        else
        {
            block.push_back(new Block(BLUE));
            blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--;                                                         //��������� �� ��������� �������.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
        }
    }

    //������� ���
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        block.push_back(new Block(ORANGE));
        blk = block.end();                                            //�������� ������������� �� ����� ������� �� ��������� ��������� �����
        blk--;                                                         //��������� �� ��������� �������.
        (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //������������� ������� �����
       
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
            block.push_back(new Block(GREEN));
            positionY = j;
            blk = block.end(); //�������� ������������� �� ����� ������� �� ��������� ��������� �����
            blk--; //��������� �� ��������� �������.
            (*blk)->setPosition(40 + j * 55, 60 + i * 23);
        }
        color += 2;
    }

    return 3;
}






