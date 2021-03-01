

#include "Ball.h"
#include "Menu.h"



Ball::Ball(Image& img, float acceleration, bool flagInit) : GameObject(img)
{   
    this->setTexture(_texture);
    this->setTextureRect(sf::IntRect(BLUE_BALL_LEFT, BLUE_BALL_TOP, BLUE_BALL_WIDTH, BLUE_BALL_HEIGHT));
   
    _acceleration = acceleration;
   
   _flagInit = flagInit;
   _flagCatch = false;
   
   _ballCounter++;
}



void Ball::Move(double angleUnitCircleX, double angleUnitCircleY, float time)
{
    // � ���� ���� �������� ��� ������ ������������� ����, �� ������� ������� ����� ��� ������� ������� space
    if (_flagInit)
    {
        _flagInit = false;
        _angleUnitCircle.x = angleUnitCircleX; // ���������� ����� �� ��������� ���������� (����������� ������ ������)
        _angleUnitCircle.y = angleUnitCircleY;
    }

     _speed = Vector2f (_acceleration * time * _angleUnitCircle.x, _acceleration*time* _angleUnitCircle.y); // ������ ������ ������
    
    this->move(_speed); // �������� ����������� ������� move �� ������ Sprite

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


// ������������� �������� ������� (������� ����� �����, ����� ���� ������ ������)
void Ball::SetSpeed(float acceleration)
{
    _acceleration = acceleration;
}

