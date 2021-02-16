
#include "GameObject.h"
#include "Menu.h"


//------------------------------------// GameObject //------------------------------------//

GameObject::GameObject(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY) : img(image)
{   
    texture.loadFromImage(image);
    this->coordX = coordX;
    this->coordY = coordY;
    this->width = width;
    this->height = height;
    this->speedX = speedX;
    this->speedY = speedY;
    isMove = false;
}

FloatRect GameObject::GetRect()
{
    return FloatRect(this->getPosition().x, this->getPosition().y, width, height);
}

Vector2f GameObject::GetSpeed()
{
    return Vector2f(speedX, speedY);
}

void GameObject::SetSpeed(Vector2f speed)
{
    speedX = speed.x;
    speedY = speed.y;
}

//------------------------------------// Platform //------------------------------------//

Platform::Platform(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
}

void Platform::SetPlatform(bool choicePlatformType)
{
    if (this->typePlatform == largePlatform)
    {
        this->typePlatform = mediumPlatform;
        this->setTextureRect(sf::IntRect(58, 302, 90, 31));
    }
    else if (this->typePlatform == smallPlatform)
    {
        this->typePlatform = mediumPlatform;
        this->setTextureRect(sf::IntRect(58, 302, 90, 31));
    }
    else if (this->typePlatform == mediumPlatform)
    {
        if (choicePlatformType == true)
        {
            this->typePlatform = largePlatform;
            this->setTextureRect(sf::IntRect(148, 302, 128, 31));
        }            
        else
        {
            this->typePlatform = smallPlatform;
            this->setTextureRect(sf::IntRect(0, 302, 58, 31));
        }
            
    }
}

//------------------------------------// Balls //------------------------------------//


Balls::Balls(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));

}

void Balls::Move(double unit_circle_x, double unit_circle_y, float time, Platform* platform) //���������� ����� �� ��������� ���������� (����������� ������ ������)
{
    //� ���� ���� �������� ��� ������ ������������� ����, �� ������� ������� ����� ��� ������� ������� space
    if (initialization)
    {
        initialization = false;
        angle_unit_circle_x = unit_circle_x;
        angle_unit_circle_y = unit_circle_y;
    }

    speed_vector_x = speedX * time * angle_unit_circle_x; //������ �������� �� x
    speed_vector_y = speedY * time * angle_unit_circle_y; //������ �������� �� y


    this->move(speed_vector_x, speed_vector_y); //�������� ����������� ������� move �� ������ Sprite
    
    //����� ������ ��������� ���� �� ������?

    //��������� ����������� � ����� ������� �����
    if (this->GetRect().left < 25)
    {
        this->setPosition(25, this->getPosition().y);       //���� ����� ���������� ������ ������, �� ��������������� � ����� ������� ��������� ���������
        angle_unit_circle_x = -angle_unit_circle_x;         //������ ����������� �� ��������������� �� �
    }

    //��������� ����������� � ������ �������
    if (this->GetRect().left > 760)
    {
        //���� ����� ���������� ������ ������, �� ��������������� � ����� ������� ��������� ���������
        this->setPosition(760, this->getPosition().y);
        angle_unit_circle_x = -angle_unit_circle_x;         //������ ����������� �� ��������������� �� �
    }

    //��������� ����������� � ��������
    if (this->getPosition().y < 25)
    {
        this->setPosition(this->getPosition().x, 25); //���� ����� ���������� �������, �� ��������������� � ����� ������� ��������� ���������
        angle_unit_circle_y = -angle_unit_circle_y;   // ������ ����������� �� ���������������, �� y
    }


    //����� ������� ����, �������������� � ����������. 
    //��������� ����� ��������� � ���� ���������� (��������� ���������, �������, ������� ���������
    //������ ��������� � ��������� ��������� � � ������� - ����������
    //� ������� ��������� ������� ����� ��������� ��������� �� 7 ��������, ��� ��������� � ������� ����� ����� ���� �� �������
    //������� ���������� ��������� � ����� ���������� �����������
    //� �������� ��������������� ������� ���������
    //� ��������� ����� ��������� ������, � ������ ���� � � ������� ����
    

    ball_center_x = this->GetRect().left + (this->GetRect().width / 2);       // ����� ������ �� �
    ball_center_y = this->GetRect().top + (this->GetRect().height / 2);       // ����� ������ �� y
    ball_right_x = this->GetRect().left + this->GetRect().width;              // ������ ���� �� �
    ball_left_x = this->GetRect().left;                                       // ����� ���� �� �

    platform_left_x = platform->GetRect().left;                               // ����� ���� ��������� �� �
    platform_right_x = platform->GetRect().left + platform->GetRect().width;  // ������ ���� ��������� �� �
    platform_top_y = platform->GetRect().top;                                 // ���� ���������

    if (platform->GetPlatformType() == 2)
        CollisionLargePlatform(platform);
    else
        CollisionSmallAndMediumPlatform(platform);

    //���� ����� ����
    if (this->getPosition().y > 700)
    {
        Menu::GetInstance().SetCountlives(-1);
        if (Menu::GetInstance().GetCountlives() > 0)
            this->setPosition(platform->getPosition().x + 56, platform->getPosition().y - 16);
        this->SetIsMove(false);
        this->initialization = true;
        this->score_ratio = 1;
    }
    
}

void Balls::CollisionSmallAndMediumPlatform(Platform* platform)
{
    if (this->GetRect().intersects(platform->GetRect())) //���� ����������� � ����������, �� �������� ����������� ������ �� ������� ����� � ��������� ���?
    {
        this->score_ratio = 1;
        std::cout << "---------------------------------------------------" << std::endl;
        //���� ����� ������ �� ���������� � ��������� � ������ ���� � ��������� ��������� �� �������� �� 8 �������?
        if (ball_center_x - platform_left_x >= 0 && ball_center_x - platform_left_x < 8)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //���� �� � ����������� �� ��������� � �������� � ����� ����, �� ������ ������� �����
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x > 0) //����� ���� ����� ����� ������� � ��������� � ����� ����, �� ������ ���������� �������
            {
                angle_unit_circle_x = -angle_unit_circle_x; //���������� �� �
                angle_unit_circle_y = -angle_unit_circle_y; //���������� �� y
            }
            else if ((speed_vector_x < 0)) //����� ���� ����� ������ ������ � ��������� � ����� ����, �� ������ �������� ������ ��������
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }
        else if (platform_right_x - ball_center_x >= 0 && platform_right_x - ball_center_x < 8)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //���� �� � ����������� �� ��������� � �������� � ������ ����, �� ������ ������� ������
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x < 0) //����� ���� ����� ������ ������ � ��������� � ������ ����, �� ������ ���������� �������
            {
                angle_unit_circle_x = -angle_unit_circle_x; //���������� �� �
                angle_unit_circle_y = -angle_unit_circle_y; //���������� �� y
            }
            else if ((speed_vector_x > 0)) //����� ���� ����� ����� ������� � ��������� � ������ ����, �� ������ �������� ������ ��������
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }
        else if (ball_center_x - platform_left_x > 0 && ball_center_x - platform_right_x < 0)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������
            angle_unit_circle_y = -angle_unit_circle_y; //� ������ ������ ����������� ��������
        }

        //������ ������������ ��������� � ����� � ������ ������ ���������

        //���� ������ ������ ����� ��������� ����� ������ ���������, � ����� ������ ������ �� ��������� ����� ������ ���������
        //��� ���� ����� ������ �� y ��������� ���� �������� ������ ���������:
        if (ball_right_x >= platform_left_x && ball_left_x < platform_left_x && ball_center_y > platform_top_y)
        {

            //����������� ����� �� ���������
            this->setPosition(platform_left_x - this->GetRect().width, this->getPosition().y);

            angle_unit_circle_x = -1 * abs(angle_unit_circle_x); //������� ����� � ��������������� �� ��������� �����������
        }
        //���� ����� ������ ������ ��������� ������ ���������, � ������ ������ ������ ������� ���������
        //��� ���� ����� ������ �� y ��������� ���� �������� ������ ���������
        else if (ball_left_x <= platform_right_x && ball_right_x > platform_right_x && ball_center_y > platform_top_y)
        {

            this->setPosition(platform_right_x, this->getPosition().y);

            angle_unit_circle_x = abs(angle_unit_circle_x); //������� ����� � ��������������� �� ��������� �����������
        }
    }
}

void Balls::CollisionLargePlatform(Platform* platform)
{
    if (this->GetRect().intersects(platform->GetRect())) //���� ����������� � ����������, �� �������� ����������� ������ �� ������� ����� � ��������� ���?
    {
        this->score_ratio = 1;
        std::cout << "---------------------------------------------------" << std::endl;
        //���� ����� ������ �� ���������� � ��������� � ������ ���� � ��������� ��������� �� �������� �� 8 �������?
        if (ball_center_x - platform_left_x >= 0 && ball_center_x - platform_left_x < 8)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //���� �� � ����������� �� ��������� � �������� � ����� ����, �� ������ ������� �����
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x > 0) //����� ���� ����� ����� ������� � ��������� � ����� ����, �� ������ ���������� �������
            {
                angle_unit_circle_x = -angle_unit_circle_x; //���������� �� �
                angle_unit_circle_y = -angle_unit_circle_y; //���������� �� y
            }
            else if ((speed_vector_x < 0)) //����� ���� ����� ������ ������ � ��������� � ����� ����, �� ������ �������� ������ ��������
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }

        //���� ����� ������ �� ���������� � ��������� � ��������� �� 8 �� 16 ������� (���� ��������� �� ��� �� ����)
        else if (ball_center_x - platform_left_x >= 8 && ball_center_x - platform_left_x < 16)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //���� �� � ����������� �� ��������� � �������� � ����� ����, �� ������ ������ �������� ���� ����������
            {
                angle_unit_circle_x += -0.19;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x < 0) //����� ���� ����� ������ ������ � ��������� � ����� ����, �� ������ ���������� ������ �� ���� ������� ����
            {
                if (angle_unit_circle_x > -0.8)     //�������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
                    angle_unit_circle_x += -0.19;   //���������� ����

                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2)); //������� ���� �� � � ������������ � �
            }
            // �����, ���� ����� ����� ������� �� �� ������ ����������� �������� �� �, � ������ �� y
            else
                angle_unit_circle_y = -angle_unit_circle_y;

        }

        //���� ����� ������ �� ���������� � ��������� � ��������� �� 16 �� 58 �������
        else if (ball_center_x - platform_left_x >= 16 && ball_center_x - platform_left_x < 58)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

            //���� �� � ����������� �� ��������� � �������� � ����� ����� ���������, �� ������ ������ �������� ���� ���������� ������ �����
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001)
            {
                angle_unit_circle_x += -0.5;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            //���� ����� ������ ������ ��� ����� �������, �� ������ �������� �������� ������ �� y
            else
                angle_unit_circle_y = -angle_unit_circle_y;
        }

        //���� ������ � ����� ��������� � ������� �� 58 �� 72 �������
        else if (ball_center_x - platform_left_x >= 58 && ball_center_x - platform_left_x < 72)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

            //���� �� � ����������� �� ��������� � �������� � ����������� ����� ���������, �� ������ ������� ���� ������, ���� ����� � ����������� ��
            //��������� ���������� change_angel
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001)
            {
                if (change_angle)
                {
                    angle_unit_circle_x = 0.5;
                    change_angle = false;
                }
                else
                    angle_unit_circle_x = -0.5;

                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else //����� ���� ��������� ����� ������� ��� ������ ������, �� �������� ������ ����������� �����
            {
                angle_unit_circle_x = 0;
                angle_unit_circle_y = 1;
            }
        }

        //���� ����� ������ �� ���������� � ��������� � ��������� �� 72 �� 113 �������
        else if (ball_center_x - platform_left_x >= 72 && ball_center_x - platform_left_x < 113)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

            //���� �� � ����������� �� ��������� � �������� � ������ ����� ���������, �� ������ ������ �������� ���� ���������� ������ ������
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001)
            {
                angle_unit_circle_x += 0.5;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            //���� ����� ������ ������ ��� ����� �������, �� ������ �������� �������� ������ �� y
            else
                angle_unit_circle_y = -angle_unit_circle_y;
        }

        //���� ����� ������ �� ���������� � ��������� � ��������� �� 113 �� 120 ������� (���� ��������� �� �� ����)
        else if (ball_center_x - platform_left_x >= 113 && ball_center_x - platform_left_x < 120)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //���� �� � ����������� �� ��������� � �������� � ������ ����, �� ������ ������ �������� ���� ����������
            {
                angle_unit_circle_x += 0.19;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x > 0) //����� ���� ����� ����� ������� � ��������� � ������ ����, �� ������ ���������� ������� �� ���� ������� ����
            {
                if (angle_unit_circle_x < 0.8)     //��������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
                    angle_unit_circle_x += 0.19;   //����������� ����

                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2)); //�������� ���� �� � � ������������ � ����� ������������ �� �
            }
            // �����, ���� ����� ������ ������ �� �� ������ ����������� �������� �� �, � ������ �� y
            else
                angle_unit_circle_y = -angle_unit_circle_y;
        }

        //���� ����� ������ �� ���������� � ��������� � ������� ���� � ��������� ��������� �� 120 �� 128 �������?
        else if (ball_center_x - platform_left_x >= 120 && ball_center_x - platform_left_x < 128)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //���� �� � ����������� �� ��������� � �������� � ������ ����, �� ������ ������� ������
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x < 0) //����� ���� ����� ������ ������ � ��������� � ������ ����, �� ������ ���������� �������
            {
                angle_unit_circle_x = -angle_unit_circle_x; //���������� �� �
                angle_unit_circle_y = -angle_unit_circle_y; //���������� �� y
            }
            else if ((speed_vector_x > 0)) //����� ���� ����� ����� ������� � ��������� � ������ ����, �� ������ �������� ������ ��������
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }

        //������ ������������ ��������� � ����� � ������ ������ ���������

        //���� ������ ������ ����� ��������� ����� ������ ���������, � ����� ������ ������ �� ��������� ����� ������ ���������
        //��� ���� ����� ������ �� y ��������� ���� �������� ������ ���������:
        if (ball_right_x >= platform_left_x && ball_left_x < platform_left_x && ball_center_y > platform_top_y)
        {

            //����������� ����� �� ���������
            this->setPosition(platform_left_x - this->GetRect().width, this->getPosition().y);

            angle_unit_circle_x = -1 * abs(angle_unit_circle_x); //������� ����� � ��������������� �� ��������� �����������
        }
        //���� ����� ������ ������ ��������� ������ ���������, � ������ ������ ������ ������� ���������
        //��� ���� ����� ������ �� y ��������� ���� �������� ������ ���������
        else if (ball_left_x <= platform_right_x && ball_right_x > platform_right_x && ball_center_y > platform_top_y)
        {

            this->setPosition(platform_right_x, this->getPosition().y);

            angle_unit_circle_x = abs(angle_unit_circle_x); //������� ����� � ��������������� �� ��������� �����������
        }
    }

}




void Balls::SetSpeedFast(int x)
{
    speedX *= 2;
    speedY *= 2;

}

void Balls::SetSpeedSlow(int x)
{
    speedX /= 2;
    speedY /= 2;

}

void Balls::ChangeVector(int x)
{
    if (x == 0)
        angle_unit_circle_x = -angle_unit_circle_x;
    else if (x == 1)
        angle_unit_circle_y = -angle_unit_circle_y;
    else if (x == 2)
    {
        angle_unit_circle_x = -angle_unit_circle_x;
        angle_unit_circle_y = -angle_unit_circle_y;
    }
    else
        std::cout << "bad index: " << x << std::endl;


}


//------------------------------------// Bonus //------------------------------------//

Bonus::Bonus(Image& image, float coordX, float coordY, float width, float height, unsigned bonusType, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->bonusType = bonusType;
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
}

void Bonus::CollisionAndMove(std::list<Bonus*>& bonuses, std::list<Bonus*>::iterator bns, Platform& platform, float time)
{
    for (bns = bonuses.begin(); bns != bonuses.end();)
    {
        (*bns)->move(0, (0.1 * time));

        if ((*bns)->GetRect().intersects(platform.GetRect()))
        {
            switch ((*bns)->bonusType)
            {
            case blue:
                break;
            case green:
                break;
            case pink:
                break;
            case purple:
                break;
            case red:
                break;
            case yellow:
                break;
            default:
                break;
            }

            bns = bonuses.erase(bns);
        }

        else
            bns++;
    }
}

//------------------------------------// Block //------------------------------------//

Block::Block(Image& image, float coordX, float coordY, float width, float height, unsigned blockType, bool bonus, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->blockType = blockType;
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
}

bool Block::Collision(std::list<Block*>& blocks, std::list<Block*>::iterator blks, Balls& ball, std::list<Bonus*>& bonuses, std::list<Bonus*>::iterator bns)
{
    float ball_left_x = ball.GetRect().left;                                        // ����� ���� ������
    float ball_right_x = ball.GetRect().left + ball.GetRect().width;                // ������ ���� �����
    float ball_top_y = ball.GetRect().top;                                          // ���� ������
    float ball_bottom_y = ball.GetRect().top + ball.GetRect().height;               // ��� ������
    float ball_center_x = ball.GetRect().left + (ball.GetRect().width / 2);
    float ball_center_y = ball.GetRect().top + (ball.GetRect().height / 2);

    //������������ ���������� � �������
    for (blks = blocks.begin(); blks != blocks.end();)
    {
        //���� ����� ������� ����, ��������� �������� �� ��� ����� � � ����� ������� ��������� ������������, � ����� ������������ ����
        if ((*blks)->GetRect().intersects(ball.GetRect())) 
        {
            Menu::GetInstance().SetCountScore(10*ball.GetScoreRatio());
            std::cout << "ball.GetScoreRatio(): " << ball.GetScoreRatio() << std::endl;
            ball.IncreaseValue_ScoreRatio();

            if ((*blks)->bonus)
                bonuses.push_back(new Bonus((*blks)->img, 594, 374, 54, 22, (*blks)->blockType));

            
            
            if (ball_top_y <= (*blks)->GetRect().top + (*blks)->GetRect().height // ���� ����� ������������� � ������ �����
                && ball_bottom_y > (*blks)->GetRect().top + (*blks)->GetRect().height
                && ball_center_x >= (*blks)->GetRect().left
                && ball_center_x <= (*blks)->GetRect().left + (*blks)->GetRect().width)
            {
                //������������� ������� ������ � ����������� ��������� ������� ��������� � ����� � ������ ������ �������� �� y
                ball.setPosition(ball.getPosition().x, (*blks)->GetRect().top + (*blks)->GetRect().height);
                ball.ChangeVector(1);
            }
            else if (ball_top_y < (*blks)->GetRect().top // ����� ���� ����� ������������� � ������ ������
                && ball_bottom_y >= (*blks)->GetRect().top
                && ball_center_x >= (*blks)->GetRect().left
                && ball_center_x <= (*blks)->GetRect().left + (*blks)->GetRect().width)
            {
                //������������� ������� ������ � ����������� ��������� ������� ��������� � ����� � ������ ������ �������� �� y
                ball.setPosition(ball.getPosition().x, (*blks)->GetRect().top - ball.GetRect().height);
                ball.ChangeVector(1);
            }

            else if (ball_left_x < (*blks)->GetRect().left //����� ���� ��������� � ����� ������� �����
                && ball_right_x >= (*blks)->GetRect().left)
                //&& ball_center_y >= (*blks)->GetRect().top
                //&& ball_center_y <= (*blks)->GetRect().top + (*blks)->GetRect().height)
            {
                //������������� ������� ������ � ����������� ��������� ������� ��������� � ����� � ������ ������ �������� �� �
                ball.setPosition((*blks)->GetRect().left - ball.GetRect().width, ball.getPosition().y);
                ball.ChangeVector(0);
            }

            else if (ball_left_x <= (*blks)->GetRect().left + (*blks)->GetRect().width //����� ���� ��������� � ������ ������� �����
                && ball_right_x > (*blks)->GetRect().left + (*blks)->GetRect().width)
                //&& ball_center_y >= (*blks)->GetRect().top
                //&& ball_center_y <= (*blks)->GetRect().top + (*blks)->GetRect().height)
            {
                //������������� ������� ������ � ����������� ��������� ������� ��������� � ����� � ������ ������ �������� �� �
                ball.setPosition((*blks)->GetRect().left + (*blks)->GetRect().width, ball.getPosition().y);
                ball.ChangeVector(0);
            }

            blks = blocks.erase(blks);
        }

        else
            blks++;

        if (blocks.empty())
        {
            return true;
        }
    }

    return false;
}



