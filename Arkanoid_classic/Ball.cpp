

#include "Ball.h"
#include "Menu.h"



Ball::Ball(float acceleration)    
{  
    this->setTexture(_texture);
    this->setTextureRect(sf::IntRect(BLUE_BALL_LEFT, BLUE_BALL_TOP, BLUE_BALL_WIDTH, BLUE_BALL_HEIGHT));
   _acceleration = acceleration;
   _flagInit = true;
   _flagMove = false;
}



void Ball::Move(double angleUnitCircleX, double angleUnitCircleY, float time, CreatorPlatform* creatorPlatform)
{
    // � ���� ���� �������� ��� ������ ������������� ����, �� ������� ������� ����� ��� ������� ������� space
    if (_flagInit)
    {
        _flagInit = false;
        _angleUnitCircle.x = angleUnitCircleX; // ���������� ����� �� ��������� ���������� (����������� ������ ������)
        _angleUnitCircle.y = angleUnitCircleY;
    }

     _speed = Vector2f (_acceleration * time * _angleUnitCircle.x, _acceleration*time* _angleUnitCircle.y); //������ ������ ������
    
    this->move(_speed); //�������� ����������� ������� move �� ������ Sprite


    // ����� ������ ��������� ���� �� ������?

    // ��������� ����������� � ����� ������� �����
    if (this->GetRect().left < BORDER_LEFT)
    {
        this->setPosition(BORDER_LEFT, this->getPosition().y);      //���� ����� ���������� ������ ������, �� ��������������� � ����� ������� ��������� ���������
        _angleUnitCircle.x = -_angleUnitCircle.x;                    //������ ����������� �� ��������������� �� �
    }

    //��������� ����������� � ������ �������
    if (this->GetRect().left+this->GetRect().width > BORDER_RIGHT)
    {
        //���� ����� ���������� ������ ������, �� ��������������� � ����� ������� ��������� ���������
        this->setPosition(BORDER_RIGHT-this->GetRect().width, this->getPosition().y);
        _angleUnitCircle.x = -_angleUnitCircle.x;          //������ ����������� �� ��������������� �� �
    }

    //��������� ����������� � ��������
    if (this->getPosition().y < BORDER_TOP)
    {
        this->setPosition(this->getPosition().x, BORDER_TOP); //���� ����� ���������� �������, �� ��������������� � ����� ������� ��������� ���������
        _angleUnitCircle.y = -_angleUnitCircle.y;    // ������ ����������� �� ���������������, �� y
    }

    // ��������� ������������ � ����������
    if (this->GetRect().intersects(creatorPlatform->GetInstance()->GetRect()))
    {
        _angleUnitCircle = creatorPlatform->GetInstance()->CollisionWithBall(_angleUnitCircle, *this);
    }
    

    //���� ����� ����
    if (this->getPosition().y > BORDER_BOTTOM)
    {
       // Menu::GetInstance().SetCountlives(-1);
        creatorPlatform = new CreatorMediumPlatform();
        this->SetFlagInit(true);
        this->SetFlagMove(false);
    }

}


// ����������� �������� ������ � ��� ����
void Ball::SetSpeedFast()
{
    _acceleration *= 2;
}

// ��������� �������� ������ � ��� ����
void Ball::SetSpeedSlow()
{
    _acceleration /= 2;
}

void Ball::SetSpeed(float acceleration)
{
    _acceleration = acceleration;
}

