

#include "MusicAndSounds.h"
#include "Ball.h"
#include "Menu.h"



Ball::Ball(Image& img, float acceleration, bool flagInit) : GameObject(img)
{   
    this->setTexture(_texture);
    this->setTextureRect(sf::IntRect(BLUE_BALL_LEFT, BLUE_BALL_TOP, BLUE_BALL_WIDTH, BLUE_BALL_HEIGHT));
   
    _acceleration = acceleration;
   
   _flagInit = flagInit;
   _flagCatch = false;
   _flagBallCatchPosition = false;
   _catchCounter = 0;
   
   _ballCounter++;
}



void Ball::Move(double angleUnitCircleX, double angleUnitCircleY, float time)
{
    // В этот блок попадаем при первой инициализации угла, на который вылетит шарик при нажатии клавиши space
    if (_flagInit)
    {
        _flagInit = false;
        _angleUnitCircle.x = angleUnitCircleX; // Координаты точки на единичной окружности (направление полета шарика)
        _angleUnitCircle.y = angleUnitCircleY;
    }

     _speed = Vector2f (_acceleration * time * _angleUnitCircle.x, _acceleration*time* _angleUnitCircle.y); // Вектор полета шарика
    
    this->move(_speed); // Вызываем стандартную функцию move от класса Sprite

}


// Увеличиваем скорость шарика в два раза
void Ball::SetSpeedFast()
{
    if (_acceleration < 0.8)
    {
        _acceleration += 0.1;
    }
    
}

// Уменьшаем скорость шарика в два раза
void Ball::SetSpeedSlow()
{
    if (_acceleration >= 0.3)
    {
        _acceleration /= 2;
    }
    if (_acceleration < 0.3)
    {
        _acceleration = 0.3;
    }
        
}


// Сбрасываем скорость в начальную
void Ball::ResetSpeed()
{
    _acceleration = 0.3;
}



void Ball::CollisionWithLeftWall()
{
    this->setPosition(BORDER_LEFT, this->getPosition().y);                                            // if intersect left wall  
    this->SetAngleUnitCircle(Vector2f(-this->GetAngleUnitCircle().x, this->GetAngleUnitCircle().y));  // change direction move
    MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
}

void Ball::CollisionWithRightWall()
{    
    this->setPosition(BORDER_RIGHT - this->GetRect().width, this->getPosition().y);                  // if intersect Right wall
    this->SetAngleUnitCircle(Vector2f(-this->GetAngleUnitCircle().x, this->GetAngleUnitCircle().y)); // change direction move
    MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
}

void Ball::CollisionWithTop()
{
    this->setPosition(this->getPosition().x, BORDER_TOP);                                                 // if intersect Top
    this->SetAngleUnitCircle(Vector2f(this->GetAngleUnitCircle().x, -this->GetAngleUnitCircle().y));      // change direction move
    MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
}

