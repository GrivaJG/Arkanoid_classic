#include "Ball.h"

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
        {
            platform->ResetTypePlatform();
            this->setPosition(platform->getPosition().x + 56, platform->getPosition().y - 16);
        }

        this->ResetBallPositionOnPlatform();
        this->ResetGreenBonus();
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
        if (greenBonus)
        {
            initialization = true;
            SetIsMove(false);
            this->SetBallPositionOnPlatform(this->GetRect().left - platform->GetRect().left);

        }
        //���� ����� ������ �� ���������� � ��������� � ������ ���� � ��������� ��������� �� �������� �� 8 �������?
        else if (ball_center_x - platform_left_x >= 0 && ball_center_x - platform_left_x < 8)
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
                {
                    angle_unit_circle_x = -0.5;
                    change_angle = true;
                }
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }

            else
                angle_unit_circle_y = -angle_unit_circle_y; //������ ������ ����������� ��������
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

        if (greenBonus)
        {
            initialization = true;
            SetIsMove(false);
            this->SetBallPositionOnPlatform(this->GetRect().left - platform->GetRect().left);
        }

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
                {
                    angle_unit_circle_x = -0.5;
                    change_angle = true;
                }



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