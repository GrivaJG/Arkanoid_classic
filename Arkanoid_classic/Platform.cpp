
#include "Platform.h"
#include "Config.h"



//-------------------------------------------------------------------------Platform

//�������� ���������
void Platform::Move(const float speed, const float time)
{
    this->move(speed * time, 0);
}


// ����������� ��������� � �������
// �� ���� ��������� �����, ������� ���������� � ���������� � ������ ��� �������� �� ��������� ����������
// ���������� ����� ������ �������� ������ �� ��������� ����������
Vector2f Platform::CollisionWithBall(Vector2f angleUnitCircle, Ball& ball) //����������� ��������� � �������
{
    float collisionLocation = this->CollisionLocation(ball);

    // ���� ����� ������ �� ���������� � ��������� ����� ���������
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleUnitCircle, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ����� ����
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleUnitCircle, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� �������� ����� ����� � ������ �����
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionStandart(angleUnitCircle, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ������ ����
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleUnitCircle, ball);
    }
    // ���� ����� ������ �� ��������� � ��������� ������ ���������
    else
    {
        return this->BallCollisionRightWall(angleUnitCircle, ball);
    }

}

Vector2f Platform::BallCollisionLeftEdge(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //���� ������������ �� ��������� ����������� �����
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));        
    }
    else if (angleUnitCircle.x > 0) //����� ���� ����� ����� ������� � ��������� � ����� ����, �� ������ ���������� �������
    {
        angleUnitCircle.x = -angleUnitCircle.x;        //���������� �� �
        angleUnitCircle.y = -angleUnitCircle.y;        //���������� �� y                    
    }
    else if (angleUnitCircle.x < 0) // ����� ���� ����� ������ ������, �� ������ ������� ��� ������� �����
    {
        angleUnitCircle.x = -0.95;                                 //���������� �� �
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.y, 2));        //���������� �� y
    }

    return angleUnitCircle;
    

}

Vector2f Platform::BallCollisionRightEdge(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //���� ������������ �� ��������� ����������� �����
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else if (angleUnitCircle.x < 0) //����� ���� ����� c����� ������ � ��������� � ������ ����, �� ������ ���������� �������
    {
        angleUnitCircle.x = -angleUnitCircle.x;        //���������� �� �
        angleUnitCircle.y = -angleUnitCircle.y;        //���������� �� y                    
    }
    else if (angleUnitCircle.x > 0) // ����� ���� ����� ����� �������, �� ������ ������� ��� ������� �����
    {
        angleUnitCircle.x = 0.95;                                 //���������� �� �
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.y, 2));        //���������� �� y
    }

    return angleUnitCircle;


}

Vector2f Platform::BallCollisionStandart(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    // ���� �� � ����������� �� ��������� � �������� � ����������� ����� ���������, �� ������ ������� ���� ������, ���� ����� � ����������� ��
    //��������� ���������� change_angel
    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001)
    {
        std::random_device rd;
        std::mt19937 mersenne(rd());

        if (mersenne() % 2)
        {
            angleUnitCircle.x = 0.5;
        }
        else
        {
            angleUnitCircle.x = -0.5;
        }

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    // ����� ������ ������ ����������� ������ �� y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f Platform::BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
    angleUnitCircle.x = -1 * abs(angleUnitCircle.x);
    return angleUnitCircle;
}

Vector2f Platform::BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
    angleUnitCircle.x = abs(angleUnitCircle.x);
    return angleUnitCircle;
}

float Platform::CollisionLocation(Ball& ball)
{
    return ball.GetRect().left + ( ball.GetRect().width / 2 ) - this->GetRect().left;
}





//-------------------------------------------------------------------------MediumPlatform

MediumPlatform::MediumPlatform()
{   
    this->setTexture(_texture);
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
    this->setTexture(_texture);
    this->setTextureRect(IntRect(LARGE_PLATFORM_LEFT, LARGE_PLATFORM_TOP, LARGE_PLATFORM_WIDTH, LARGE_PLATFORM_HEIGHT));
}

Vector2f LargePlatform::CollisionWithBall(Vector2f angleUnitCircle, Ball& ball)
{
    float collisionLocation = this->CollisionLocation(ball);
    // ���� ����� ������ �� ���������� � ��������� ����� ���������
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleUnitCircle, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ����� ����
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleUnitCircle, ball);
    }
    // ���� ������ � ���� ��������� �������� ����, �� �� � ��� ����
    else if (collisionLocation < 16)
    {
        return this->BallCollisionLeftEdgePlus(angleUnitCircle, ball);
    }
    // ���� ������ � ����� �����
    else if (collisionLocation < 58)
    {
        return this->BallCollisionStandart(angleUnitCircle, ball);
    }
    // ���� ������ � ����� �����
    else if (collisionLocation < 72)
    {
        return this->BallCollisionCenter(angleUnitCircle, ball);
    }

    // ���� ������ � ������ �����
    else if (collisionLocation < this->GetRect().width - 16)
    {
        return this->BallCollisionStandart(angleUnitCircle, ball);
    }
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionRightEdgePlus(angleUnitCircle, ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ������ ����
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleUnitCircle, ball);
    }
    // ���� ����� ������ �� ��������� � ��������� ������ ���������
    else
    {
        return this->BallCollisionRightWall(angleUnitCircle, ball);
    }
}

Vector2f LargePlatform::BallCollisionLeftEdgePlus(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) //���� �� � ����������� �� ��������� � �������� � ����� ����, �� ������ ������ �������� ���� ����������
    {
        angleUnitCircle.x += -0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else if (angleUnitCircle.x < 0) //����� ���� ����� ������ ������ � ��������� � ����� ����, �� ������ ���������� ������ �� ���� ������� ����
    {
        if (angleUnitCircle.x > -0.8)     //��������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
            angleUnitCircle.x += -0.19;   //����������� ����

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); //�������� ���� �� � � ������������ � �
    }
    // �����, ���� ����� ����� ������� �� �� ������ ����������� �������� �� �, � ������ �� y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
        
}

Vector2f LargePlatform::BallCollisionRightEdgePlus(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) //���� �� � ����������� �� ��������� � �������� � ������ ����, �� ������ ������ �������� ���� ����������
    {
        angleUnitCircle.x += +0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else if (angleUnitCircle.x > 0) //����� ���� ����� ����� ������� � ��������� � ������ ����, �� ������ ���������� ������ �� ���� ������� ����
    {
        if (angleUnitCircle.x < 0.8)     //��������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
            angleUnitCircle.x += 0.19;   //����������� ����

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); //�������� ���� �� � � ������������ � �
    }
    // �����, ���� ����� ������ ������ �� �� ������ ����������� �������� �� �, � ������ �� y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f LargePlatform::BallCollisionCenter(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(this->getPosition().x, this->GetRect().top - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������

    std::random_device rd;
    std::mt19937 mersenne(rd());
    //���� �� � ����������� �� ��������� � �������� � ����������� ����� ���������, �� ������ ������� ���� ������, ���� ����� � ����������� ��
    //��������� ���������� change_angel
    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001)
    {
        if (mersenne()%2)
        {
            angleUnitCircle.x = 0.5;                
        }
        else
        {
            angleUnitCircle.x = -0.5;                
        }
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else //����� ���� ��������� ����� ������� ��� ������ ������, �� �������� ������ ����������� �����
    {
        angleUnitCircle.x = 0;
        angleUnitCircle.y = -1;        
    }

    return angleUnitCircle;
}




//--------------------------------------------------------------------------------------�������



void CreatorPlatform::ChangePlatform()
{   
    concretePlatform = this->FactoryMethod();
}



//FloatRect CreatorPlatform::SomeGetRect()
//{
//    FloatRect result = concretePlatform->GetRect();
//    return result;
//}
//
//void CreatorPlatform::SomeSetPosition(Vector2f position)
//{
//    concretePlatform->setPosition(position);
//    
//}
//
//void CreatorPlatform::SomeMove(const float speed, float time)
//{
//    concretePlatform->Move(speed, time);    
//}
//
//Vector2f CreatorPlatform::SomeGetPosition()
//{   
//    Vector2f result = concretePlatform->getPosition();
//    return result;
//}

void CreatorPlatform::SomeDraw(RenderWindow& window)
{
    window.draw(*concretePlatform);
}