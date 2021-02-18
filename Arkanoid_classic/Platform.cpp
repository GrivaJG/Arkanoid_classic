#include "Platform.h"


//-------------------------------------------------------------------------Platform

//�������� ���������
void Platform::Move(const int& speed, const float& time)
{
    this->move(speed * time, 0);
}


// ����������� ��������� � �������
// �� ���� ��������� �����, ������� ���������� � ���������� � ������ ��� �������� �� ��������� ����������
// ���������� ����� ������ �������� ������ �� ��������� ����������
Vector2f Platform::CollisionWithBall(Vector2f angleFlyBall, Ball& ball) //����������� ��������� � �������
{
    float collisionLocation = this->CollisionLocation(ball);

    // ���� ����� ������ �� ���������� � ��������� ����� ���������
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleFlyBall, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ����� ����
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleFlyBall, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� �������� ����� ����� � ������ �����
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionStandart(angleFlyBall, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ������ ����
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleFlyBall, ball);
    }
    // ���� ����� ������ �� ��������� � ��������� ������ ���������
    else
    {
        return this->BallCollisionRightWall(angleFlyBall, ball);
    }

}

Vector2f Platform::BallCollisionLeftEdge(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //���� ������������ �� ��������� ����������� �����
    if (angleFlyBall.x > -0.001 && angleFlyBall.x < 0.001)
    {
        angleFlyBall.x = -0.9;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));        
    }
    else if (angleFlyBall.x > 0) //����� ���� ����� ����� ������� � ��������� � ����� ����, �� ������ ���������� �������
    {
        angleFlyBall.x = -angleFlyBall.x;        //���������� �� �
        angleFlyBall.y = -angleFlyBall.y;        //���������� �� y                    
    }
    else if (angleFlyBall.x < 0) // ����� ���� ����� ������ ������, �� ������ ������� ��� ������� �����
    {
        angleFlyBall.x = -0.95;                                 //���������� �� �
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.y, 2));        //���������� �� y
    }

    return angleFlyBall;
    

}

Vector2f Platform::BallCollisionRightEdge(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //���� ������������ �� ��������� ����������� �����
    if (angleFlyBall.x > -0.001 && angleFlyBall.x < 0.001)
    {
        angleFlyBall.x = -0.9;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else if (angleFlyBall.x < 0) //����� ���� ����� c����� ������ � ��������� � ������ ����, �� ������ ���������� �������
    {
        angleFlyBall.x = -angleFlyBall.x;        //���������� �� �
        angleFlyBall.y = -angleFlyBall.y;        //���������� �� y                    
    }
    else if (angleFlyBall.x > 0) // ����� ���� ����� ����� �������, �� ������ ������� ��� ������� �����
    {
        angleFlyBall.x = 0.95;                                 //���������� �� �
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.y, 2));        //���������� �� y
    }

    return angleFlyBall;


}

Vector2f Platform::BallCollisionStandart(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    // ���� �� � ����������� �� ��������� � �������� � ����������� ����� ���������, �� ������ ������� ���� ������, ���� ����� � ����������� ��
    //��������� ���������� change_angel
    if (angleFlyBall.x < 0.001 && angleFlyBall.y > -0.001)
    {
        std::random_device rd;
        std::mt19937 mersenne(rd());

        if (mersenne() % 2)
        {
            angleFlyBall.x = 0.5;
        }
        else
        {
            angleFlyBall.x = -0.5;
        }

        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    // ����� ������ ������ ����������� ������ �� y
    else
    {
        angleFlyBall.y = -angleFlyBall.y;
    }

    return angleFlyBall;
}

Vector2f Platform::BallCollisionLeftWall(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
    angleFlyBall.x = -1 * abs(angleFlyBall.x);
}

Vector2f Platform::BallCollisionRightWall(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
    angleFlyBall.x = abs(angleFlyBall.x);
}

float Platform::CollisionLocation(Ball& ball)
{
    return ball.GetRect().left + ( ball.GetRect().width / 2 ) - this->GetRect().left;
}





//-------------------------------------------------------------------------MediumPlatform

MediumPlatform::MediumPlatform()
{   
    this->setTextureRect(IntRect(MEDIUM_PLATFORM_LEFT, MEDIUM_PLATFORM_TOP, MEDIUM_PLATFORM_WIDTH, MEDIUM_PLATFORM_HEIGHT));
    
}



//--------------------------------------------------------------------------SmallPlatform
SmallPlatform::SmallPlatform()
{
    this->setTextureRect(IntRect(SMALL_PLATFORM_LEFT, SMALL_PLATFORM_TOP, SMALL_PLATFORM_WIDTH, SMALL_PLATFORM_HEIGHT));
}



//-------------------------------------------------------------------------------LargePlatform

LargePlatform::LargePlatform()
{
    this->setTextureRect(IntRect(LARGE_PLATFORM_LEFT, LARGE_PLATFORM_TOP, LARGE_PLATFORM_WIDTH, LARGE_PLATFORM_HEIGHT));
}

Vector2f LargePlatform::CollisionWithBall(Vector2f angleFlyBall, Ball& ball)
{
    float collisionLocation = this->CollisionLocation(ball);
    // ���� ����� ������ �� ���������� � ��������� ����� ���������
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleFlyBall, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ����� ����
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleFlyBall, ball);
    }
    // ���� ������ � ���� ��������� �������� ����, �� �� � ��� ����
    else if (collisionLocation < 16)
    {
        return this->BallCollisionLeftEdgePlus(angleFlyBall, ball);
    }
    // ���� ������ � ����� �����
    else if (collisionLocation < 58)
    {
        return this->BallCollisionStandart(angleFlyBall, ball);
    }
    // ���� ������ � ����� �����
    else if (collisionLocation < 72)
    {
        return this->BallCollisionCenter(angleFlyBall, ball);
    }

    // ���� ������ � ������ �����
    else if (collisionLocation < this->GetRect().width - 16)
    {
        return this->BallCollisionStandart(angleFlyBall, ball);
    }
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionRightEdgePlus(angleFlyBall, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ������ ����
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleFlyBall, ball);
    }
    // ���� ����� ������ �� ��������� � ��������� ������ ���������
    else
    {
        return this->BallCollisionRightWall(angleFlyBall, ball);
    }
}

Vector2f LargePlatform::BallCollisionLeftEdgePlus(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

    if (angleFlyBall.x < 0.001 && angleFlyBall.x > -0.001) //���� �� � ����������� �� ��������� � �������� � ����� ����, �� ������ ������ �������� ���� ����������
    {
        angleFlyBall.x += -0.35;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else if (angleFlyBall.x < 0) //����� ���� ����� ������ ������ � ��������� � ����� ����, �� ������ ���������� ������ �� ���� ������� ����
    {
        if (angleFlyBall.x > -0.8)     //��������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
            angleFlyBall.x += -0.19;   //����������� ����

        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2)); //�������� ���� �� � � ������������ � �
    }
    // �����, ���� ����� ����� ������� �� �� ������ ����������� �������� �� �, � ������ �� y
    else
    {
        angleFlyBall.y = -angleFlyBall.y;
    }

    return angleFlyBall;
        
}

Vector2f LargePlatform::BallCollisionRightEdgePlus(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

    if (angleFlyBall.x < 0.001 && angleFlyBall.x > -0.001) //���� �� � ����������� �� ��������� � �������� � ������ ����, �� ������ ������ �������� ���� ����������
    {
        angleFlyBall.x += +0.35;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else if (angleFlyBall.x > 0) //����� ���� ����� ����� ������� � ��������� � ������ ����, �� ������ ���������� ������ �� ���� ������� ����
    {
        if (angleFlyBall.x < 0.8)     //��������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
            angleFlyBall.x += 0.19;   //����������� ����

        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2)); //�������� ���� �� � � ������������ � �
    }
    // �����, ���� ����� ������ ������ �� �� ������ ����������� �������� �� �, � ������ �� y
    else
    {
        angleFlyBall.y = -angleFlyBall.y;
    }

    return angleFlyBall;
}

Vector2f LargePlatform::BallCollisionCenter(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(this->getPosition().x, this->GetRect().top - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

    std::random_device rd;
    std::mt19937 mersenne(rd());
    //���� �� � ����������� �� ��������� � �������� � ����������� ����� ���������, �� ������ ������� ���� ������, ���� ����� � ����������� ��
    //��������� ���������� change_angel
    if (angleFlyBall.x < 0.001 && angleFlyBall.x > -0.001)
    {
        if (mersenne()%2)
        {
            angleFlyBall.x = 0.5;                
        }
        else
        {
            angleFlyBall.x = -0.5;                
        }
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else //����� ���� ��������� ����� ������� ��� ������ ������, �� �������� ������ ����������� �����
    {
        angleFlyBall.x = 0;
        angleFlyBall.y = 1;        
    }

    return angleFlyBall;
}




//--------------------------------------------------------------------------------------�������

Vector2f CreatorPlatform::SomeCollisionWithBall(Vector2f angleFlyBall, Ball& ball)
{
    Platform* platform = this->FactoryMethod();

    Vector2f result = platform->CollisionWithBall(angleFlyBall, ball);

    delete platform;
    return  result;
}

FloatRect CreatorPlatform::SomeGetRect()
{
    Platform* platform = this->FactoryMethod();

    FloatRect result = platform->GetRect();
    delete platform;
    return result;
}