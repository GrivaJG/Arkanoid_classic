
#include "Config.h"
#include "Ball.h"

#include "Block.h"

Block::Block(Image& img, BlockType block_type, bool flag_bonus) : GameObject(img)
{
    m_flag_bonus = flag_bonus;
    m_block_type = block_type;
    this->setTexture(m_texture);

    if (m_flag_bonus)
    {
        switch (m_block_type)
        {
        case BLUE:
            this->setTextureRect(sf::IntRect(BLUE_BONUS_BLOCK_LEFT, BLUE_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case GREEN:
            this->setTextureRect(sf::IntRect(GREEN_BONUS_BLOCK_LEFT, GREEN_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case ORANGE:
            this->setTextureRect(sf::IntRect(ORANGE_BLOCK_LEFT, ORANGE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PINK:
            this->setTextureRect(sf::IntRect(PINK_BONUS_BLOCK_LEFT, PINK_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PURPLE:
            this->setTextureRect(sf::IntRect(PURPLE_BONUS_BLOCK_LEFT, PURPLE_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case RED:
            this->setTextureRect(sf::IntRect(RED_BONUS_BLOCK_LEFT, RED_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case YELLOW:
            this->setTextureRect(sf::IntRect(YELLOW_BONUS_BLOCK_LEFT, YELLOW_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        default:
            throw ("invalid argument block_type");
            break;
        }
    }
    else
    {
        switch (m_block_type)
        {
        case BLUE:
            this->setTextureRect(sf::IntRect(BLUE_BLOCK_LEFT, BLUE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case GREEN:
            this->setTextureRect(sf::IntRect(GREEN_BLOCK_LEFT, GREEN_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case ORANGE:
            this->setTextureRect(sf::IntRect(ORANGE_BLOCK_LEFT, ORANGE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PINK:
            this->setTextureRect(sf::IntRect(PINK_BLOCK_LEFT, PINK_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PURPLE:
            this->setTextureRect(sf::IntRect(PURPLE_BLOCK_LEFT, PURPLE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case RED:
            this->setTextureRect(sf::IntRect(RED_BLOCK_LEFT, RED_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case YELLOW:
            this->setTextureRect(sf::IntRect(YELLOW_BLOCK_LEFT, YELLOW_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        default:
            throw ("invalid argument blockType");
            break;
        }
    }
}

Vector2f Block::BallCollision(Ball& ball)
{
    float ball_leftX = ball.GetRect().left;                                        // Left edge ball
    float ball_rightX = ball.GetRect().left + ball.GetRect().width;                // Right edge ball
    float ball_topY = ball.GetRect().top;                                          // Top ball
    float ball_bottomY = ball.GetRect().top + ball.GetRect().height;               // Bottom ball
    float ball_centerX = ball.GetRect().left + (ball.GetRect().width / 2);         // Coord center ball X
    float ball_centerY = ball.GetRect().top + (ball.GetRect().height / 2);         // Coord center ball Y

    float block_bottomY = this->GetRect().top + this->GetRect().height;             // Bottom block
    float block_topY = this->GetRect().top;                                         // Top block
    float block_leftX = this->GetRect().left;                                       // Left edge block
    float block_rightX = this->GetRect().left + this->GetRect().width;              // Right edge block
    


    // Collision with left bottom corner
    if (ball_centerX < block_leftX && ball_centerY > block_bottomY)                     // Po X - center sharika nahoditsya levee chem left edge blocka
    {                                                                               // Po Y - center sharika nahoditsya nige chem bottom blocka              
        return BallCollisionLeftBottomCorner(ball);
    }    
    // Collision with left top corner
    else if (ball_centerX < block_leftX && ball_centerY < block_topY)                   // Po X - center sharika nahoditsya levee chem left edge blocka                                                         
    {                                                                               // Po Y - center sharika nahoditsya vishe chem bottom blocka       
        return BallCollisionLeftTopCorner(ball);
    }

    // Collision with right top corner
    else if (ball_centerX > block_rightX && ball_centerY < block_topY)                 // Po X - center sharika nahoditsya pravee chem praviy edge blocka                           
    {                                                                              // Po Y - center sharika nahoditsya vishe chem bottom blocka       
        return BallCollisionRightTopCorner(ball);
    }

    // Collition with right bottom corner
    else if (ball_centerX > block_rightX && ball_centerY > block_bottomY)                // Po X - center sharika nahoditsya pravee chem praviy edge blocka      
    {                                                                                // Po Y - center sharika nahoditsya nige chem bottom blocka        
        return BallCollisionRightBottomCorner(ball);
    }

    // Collision with bottom
    else if (ball_centerX > block_leftX && ball_centerX < block_rightX                   // If po X nahodimsya v diapazone bolcka
        && ball_bottomY > block_bottomY)                                               // A po Y nahodimsa nige nignego kraya
    {        
        return BallCollisionBottomWall(ball);
    }

    // Collision with top
    else if (ball_centerX > block_leftX && ball_centerX < block_rightX                       // If po X nahodimsya v diapazone bolcka
        && ball_topY < block_topY)                                                         // A po Y nahodimsa vishe verhnego kraya
    {        
        return BallCollisionTopWall(ball);
    }

    // Collision with left wall
    else if (ball_centerY > block_topY && ball_centerY < block_bottomY                      // If po Y nahodimsya v diapazone bolcka
        && ball_leftX < block_leftX)                                                      // A po X nahodimsya sleva
    {        
        return BallCollisionLeftWall(ball);
    }

    // Collision with right wall
    else if (ball_centerY > block_topY && ball_centerY < block_bottomY                      // If po Y nahodimsya v diapazone bolcka
        && ball_rightX > block_rightX)                                                    // A po X nahodimsya sprava
    {        
        return BallCollisionRightWall(ball);
    }
    else
    {
        return ball.GetAngleUnitCircle();                                               // inache nichego ne delaem
    }
}


Vector2f Block::BallCollisionRightBottomCorner(Ball& ball)
{
    
    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();
    // If stolknovenie pod pryamim uglom to:
    if (angle_unit_circle.x > -0.001 && angle_unit_circle.x < 0.001)
    {
        ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
        angle_unit_circle.x = 0.9;                                   // Otletaem napravo
        angle_unit_circle.y = sqrt(1 - pow(angle_unit_circle.x, 2));
    }
    else 
    {
        if (angle_unit_circle.y < 0)
        {
            ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
            angle_unit_circle.y = -angle_unit_circle.y;                 // Otragaemsya tolko po Y vniz
        }
        else
        {
            ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
            angle_unit_circle.x = -angle_unit_circle.x;                 // Otragaemsya tolko po X
        }
        
    }  
    return angle_unit_circle;
}

Vector2f Block::BallCollisionLeftBottomCorner(Ball& ball)
{
    
    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();

    // If stolknovenie pod pryamim uglom to:
    if (angle_unit_circle.x > -0.001 && angle_unit_circle.x < 0.001)
    {
        ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
        angle_unit_circle.x = -0.9;                                   //otletaem nalevo
        angle_unit_circle.y = sqrt(1 - pow(angle_unit_circle.x, 2));
    }
    else
    {
        if (angle_unit_circle.y < 0)
        {
            ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
            angle_unit_circle.y = -angle_unit_circle.y;                 // Otrazhaemsya tolko po Y vniz 
        }
        else
        {
            ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
            angle_unit_circle.x = -angle_unit_circle.x;                 // Otrazhaemsya tolko po X
        }
    }   
    return angle_unit_circle;
}

Vector2f Block::BallCollisionRightTopCorner(Ball& ball)
{    
    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();

    // If stolknovenie pod pryamim uglom to:
    if (angle_unit_circle.x > -0.001 && angle_unit_circle.x < 0.001)
    {        
        ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
        angle_unit_circle.x = 0.9;                                   // Otletaem nalevo
        angle_unit_circle.y = -1* sqrt(1 - pow(angle_unit_circle.x, 2));
    }
    else
    {
        if (angle_unit_circle.y > 0)
        {            
            ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
            angle_unit_circle.y = -angle_unit_circle.y;                 // Otrazhaemsya po Y            
        }
        else
        {            
            ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
            angle_unit_circle.x = -angle_unit_circle.x;                 // Otrazhaemsya po X
        }

    }   

    return angle_unit_circle;
}

Vector2f Block::BallCollisionLeftTopCorner(Ball& ball)
{   
    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();

    // If stolknovenie pod pryamim uglom to:
    if (angle_unit_circle.x > -0.001 && angle_unit_circle.x < 0.001)
    {   
        ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
        angle_unit_circle.x = -0.9;                                   // Otletaem nalevo
        angle_unit_circle.y = -1 * sqrt(1 - pow(angle_unit_circle.x, 2));
    }
    else
    {
        if (angle_unit_circle.y > 0)
        {
            ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
            angle_unit_circle.y = -angle_unit_circle.y;                 // Otrazhaemsya po Y tolko vniz               
        }
        else
        {
            ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
            angle_unit_circle.x = -angle_unit_circle.x;                 // Otrazhaemsya tolko po X
        }

    }   
    return angle_unit_circle;
}

Vector2f Block::BallCollisionBottomWall(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->GetRect().top + BLOCK_HEIGHT);
   
    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();

    angle_unit_circle.y = abs(angle_unit_circle.y);                 //Otrazhaemsya po Y tolko vniz      

    return angle_unit_circle;
}

Vector2f Block::BallCollisionTopWall(Ball& ball)
{    
    ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);

    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();

    angle_unit_circle.y = -1 * abs(angle_unit_circle.y);                 //Otrazhaemsya po Y tolko vverh

    return angle_unit_circle;
}

Vector2f Block::BallCollisionLeftWall(Ball& ball)
{   
    ball.setPosition(this->GetRect().left-BLUE_BALL_WIDTH, ball.getPosition().y);

    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();

    angle_unit_circle.x = -1 * abs(angle_unit_circle.x);                         // Otrazhaemsya po X

    return angle_unit_circle;
}

Vector2f Block::BallCollisionRightWall(Ball& ball)
{       
    ball.setPosition(this->GetRect().left + BLOCK_WIDTH, ball.getPosition().y);

    Vector2f angle_unit_circle = ball.GetAngleUnitCircle();

    angle_unit_circle.x = -angle_unit_circle.x;                         // Otrazhaemsya po X
    
    return angle_unit_circle;
}