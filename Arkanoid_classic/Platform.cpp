
#include "Platform.h"
#include "Config.h"



//-------------------------------------------------------------------------Platform

// �������� ���������
void Platform::Move(const float speed, const float time)
{
    this->move(speed * time, 0);
}




// ����������� ��������� � �������
// �� ���� ��������� �����, ������� ���������� � ���������� � ������ ��� �������� �� ��������� ����������
// ���������� ����� ������ �������� ������ �� ��������� ����������
Vector2f Platform::CollisionWithBall(Ball& ball) //����������� ��������� � �������
{
    
    float collisionLocation = this->CollisionLocation(ball);

    // ���� ����� ������ �� ���������� � ��������� ����� ���������
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ����� ����
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� �������� ����� ����� � ������ �����
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionStandart(ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ������ ����
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(ball);
    }
    // ���� ����� ������ �� ��������� � ��������� ������ ���������
    else
    {
        return this->BallCollisionRightWall(ball);
    }

}

Vector2f Platform::BallCollisionLeftEdge(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    //���� ������������ �� ��������� ����������� �����
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x > 0) //����� ���� ����� ����� ������� � ��������� � ����� ����, �� ������ ���������� �������
    {
        angleUnitCircle.x = -angleUnitCircle.x;        //���������� �� �
        angleUnitCircle.y = -angleUnitCircle.y;        //���������� �� y                    
    }
    else if (angleUnitCircle.x < 0) // ����� ���� ����� ������ ������, �� ������ ������� ��� ������� �����
    {
        angleUnitCircle.x = -0.9;                                 //���������� �� �
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.y, 2)); 
        angleUnitCircle.y = -angleUnitCircle.y;                    //���������� �� y
    }

    return angleUnitCircle;
    

}

Vector2f Platform::BallCollisionRightEdge(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    //���� ������������ �� ��������� ����������� �����
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = 0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x < 0) //����� ���� ����� c����� ������ � ��������� � ������ ����, �� ������ ���������� �������
    {
        angleUnitCircle.x = -angleUnitCircle.x;        //���������� �� �
        angleUnitCircle.y = -angleUnitCircle.y;        //���������� �� y                    
    }
    else if (angleUnitCircle.x > 0) // ����� ���� ����� ����� �������, �� ������ ������� ��� ������� �����
    {
        angleUnitCircle.x = 0.9;                                 //���������� �� �
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.y, 2));
        angleUnitCircle.y = -angleUnitCircle.y;                      //���������� �� y
    }

    return angleUnitCircle;


}

Vector2f Platform::BallCollisionStandart(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

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
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    // ����� ������ ������ ����������� ������ �� y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f Platform::BallCollisionLeftWall(Ball& ball)
{
    //�� ���� ������ ��������� ������ ���������
    ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.x = -1 * abs(angleUnitCircle.x); // ���������� ����� ������ ����� �� ���������, �� y ���������� ������ ��� ������
    return angleUnitCircle;
}

Vector2f Platform::BallCollisionRightWall(Ball& ball)
{
    // �� ���� ������ �������� ������ ���������
    ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.x = abs(angleUnitCircle.x); //���������� ����� ������ �� ���������
    return angleUnitCircle;
}

// ���������� � ����� ����� ��������� ����� �����
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
    this->setTexture(_texture);
    this->setTextureRect(IntRect(SMALL_PLATFORM_LEFT, SMALL_PLATFORM_TOP, SMALL_PLATFORM_WIDTH, SMALL_PLATFORM_HEIGHT));
    
}



//--------------------------------------------------------------------------LargePlatform

LargePlatform::LargePlatform()
{   
    this->setTexture(_texture);
    this->setTextureRect(IntRect(LARGE_PLATFORM_LEFT, LARGE_PLATFORM_TOP, LARGE_PLATFORM_WIDTH, LARGE_PLATFORM_HEIGHT));    
}

Vector2f LargePlatform::CollisionWithBall(Ball& ball)
{
    float collisionLocation = this->CollisionLocation(ball);
    // ���� ����� ������ �� ���������� � ��������� ����� ���������
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ����� ����
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(ball);
    }
    // ���� ������ � ���� ��������� �������� ����, �� �� � ��� ����
    else if (collisionLocation < 16)
    {
        return this->BallCollisionLeftEdgePlus(ball);
    }
    // ���� ������ � ����� �����
    else if (collisionLocation < 58)
    {
        return this->BallCollisionStandart(ball);
    }
    // ���� ������ � ����� �����
    else if (collisionLocation < 72)
    {
        return this->BallCollisionCenter(ball);
    }

    // ���� ������ � ������ �����
    else if (collisionLocation < this->GetRect().width - 16)
    {
        return this->BallCollisionStandart(ball);
    }
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionRightEdgePlus(ball);
    }
    // ���� ����� ������ �� ���������� � ��������� �� ������ ����
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(ball);
    }
    // ���� ����� ������ �� ��������� � ��������� ������ ���������
    else
    {
        return this->BallCollisionRightWall(ball);
    }
}

Vector2f LargePlatform::BallCollisionLeftEdgePlus(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) //���� �� � ����������� �� ��������� � �������� � ����� ����, �� ������ ������ �������� ���� ����������
    {
        angleUnitCircle.x += -0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x < 0) //����� ���� ����� ������ ������ � ��������� � ����� ����, �� ������ ���������� ������ �� ���� ������� ����
    {
        if (angleUnitCircle.x > -0.8)     //��������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
            angleUnitCircle.x += -0.19;   //����������� ����

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); //�������� ���� �� � � ������������ � �
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    // �����, ���� ����� ����� ������� �� �� ������ ����������� �������� �� �, � ������ �� y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
        
}

Vector2f LargePlatform::BallCollisionRightEdgePlus(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //���� ��������� ���������, �� ����������� ����� �� ���������
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) //���� �� � ����������� �� ��������� � �������� � ������ ����, �� ������ ������ �������� ���� ����������
    {
        angleUnitCircle.x += +0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x > 0) //����� ���� ����� ����� ������� � ��������� � ������ ����, �� ������ ���������� ������ �� ���� ������� ����
    {
        if (angleUnitCircle.x < 0.8)     //��������� �� ������� �� ����� ����, ����� ����� �� ����� ������ ����������� ���������
            angleUnitCircle.x += 0.19;   //����������� ����

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); //�������� ���� �� � � ������������ � �
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    // �����, ���� ����� ������ ������ �� �� ������ ����������� �������� �� �, � ������ �� y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f LargePlatform::BallCollisionCenter(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->GetRect().top - ball.GetRect().height-5); //���� ��������� ���������, �� ����������� ����� �� ���������
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

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
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else //����� ���� ��������� ����� ������� ��� ������ ������, �� �������� ������ ����������� �����
    {
        
        angleUnitCircle.x = 0;
        angleUnitCircle.y = -1;        
    }

    return angleUnitCircle;
}




//------------------------------------------------------------����� ���������� ��� ������� ������� ��������



ConcretePlatform::ConcretePlatform()
{
    _smallPlatform = new SmallPlatform;
    _mediumPlatform = new MediumPlatform;
    _largePlatform = new LargePlatform;
    _concretePlatform = _mediumPlatform;
}

ConcretePlatform::~ConcretePlatform()
{
    delete _concretePlatform;
    delete _smallPlatform;
    delete _mediumPlatform;
    delete _largePlatform;
}


void ConcretePlatform::ChangePlatform(int sizePlatform)
{
    Vector2f position = _concretePlatform->getPosition();
    if (sizePlatform <= 1)
    {
        _concretePlatform = _smallPlatform;        
    }
    else if (sizePlatform == 2)
    {
        _concretePlatform = _mediumPlatform;
    }
    else
    {
        _concretePlatform = _largePlatform;
    }

    _concretePlatform->setPosition(position);
}

