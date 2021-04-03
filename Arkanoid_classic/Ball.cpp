

#include "MusicAndSounds.h"
#include "Ball.h"
#include "Menu.h"



Ball::Ball(Image& img, float acceleration, bool flag_init) : GameObject(img)
{

    this->setTexture(m_texture);
    this->setTextureRect(sf::IntRect(BLUE_BALL_LEFT, BLUE_BALL_TOP, BLUE_BALL_WIDTH, BLUE_BALL_HEIGHT));
   
    m_acceleration = acceleration;
   
    m_flag_init = flag_init;
    m_flag_catch = false;
    m_flag_ball_catch_position = false;
    m_catch_counter = 0;
    m_catch_positionX = 0;
   
    m_ball_counter++;
}



void Ball::Move(double angle_unit_circleX, double angle_unit_circleY, float time)
{
    // Block for first initialization angle. Tolko pri pervom zapuske sharika s platformi
    if (m_flag_init)
    {
        m_flag_init = false;
        m_angle_unit_circle.x = angle_unit_circleX; // Coord tochki na edinichnoi okruzhnosti 
        m_angle_unit_circle.y = angle_unit_circleY;
    }

     m_speed = Vector2f (m_acceleration * time * m_angle_unit_circle.x, m_acceleration*time* m_angle_unit_circle.y); // Vector poleta sharika
    
    this->move(m_speed); // Standart function move of SFML

}


// Increase speed
void Ball::SetSpeedFast()
{
    if (m_acceleration < MAX_BALL_SPEED)
    {
        m_acceleration += 0.1;
    }
    
}

// Decrease speed
void Ball::SetSpeedSlow()
{
    if (m_acceleration >= DEFAULT_BALL_SPEED)
    {
        m_acceleration /= 2;
    }
    if (m_acceleration < DEFAULT_BALL_SPEED)
    {
        m_acceleration = DEFAULT_BALL_SPEED;
    }
        
}


// Default speed
void Ball::ResetSpeed()
{
    m_acceleration = DEFAULT_BALL_SPEED;
}



void Ball::CollisionWithLeftWall() // If intersect left wall  
{
    this->setPosition(BORDER_LEFT, this->getPosition().y);                                            
    this->SetAngleUnitCircle(Vector2f(-this->GetAngleUnitCircle().x, this->GetAngleUnitCircle().y));  // Change direction move    
}

void Ball::CollisionWithRightWall() // If intersect Right wall
{    
    this->setPosition(BORDER_RIGHT - this->GetRect().width, this->getPosition().y);                  
    this->SetAngleUnitCircle(Vector2f(-this->GetAngleUnitCircle().x, this->GetAngleUnitCircle().y)); // Change direction move   
}

void Ball::CollisionWithTop()  // If intersect Top
{
    this->setPosition(this->getPosition().x, BORDER_TOP);                                                
    this->SetAngleUnitCircle(Vector2f(this->GetAngleUnitCircle().x, -this->GetAngleUnitCircle().y));      // Change direction move    
}

