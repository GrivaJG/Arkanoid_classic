
#include "Config.h"
#include "Block.h"


Block::Block(Image& img, BlockType blockType, bool flagBonus) : GameObject(img)
{
    _flagBonus = flagBonus;
    _blockType = blockType;
    this->setTexture(_texture);

    if (_flagBonus)
    {
        switch (_blockType)
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
            throw ("invalid argument blockType");
            break;
        }
    }
    else
    {
        switch (_blockType)
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
    float ballLeftX = ball.GetRect().left;                                        // Левый край шарика
    float ballRightX = ball.GetRect().left + ball.GetRect().width;                // Правый край ширка
    float ballTopY = ball.GetRect().top;                                          // Верх шарика
    float ballBottomY = ball.GetRect().top + ball.GetRect().height;               // Низ шарика
    float ballCenterX = ball.GetRect().left + (ball.GetRect().width / 2);         // Координаты центра шарика по х
    float ballCenterY = ball.GetRect().top + (ball.GetRect().height / 2);         // Координаты центра шарика по y

    float blockBottomY = this->GetRect().top + this->GetRect().height;             // Низ блока
    float blockTopY = this->GetRect().top;                                         // Верх блока
    float blockLeftX = this->GetRect().left;                                       // левый край блока
    float blockRightX = this->GetRect().left + this->GetRect().width;              // правый край блока
    


    // Столкновение с левым нижним углом
    if (ballCenterX < blockLeftX && ballCenterY > blockBottomY)                     // По х - центр шарика находится левее чем левый край блока,
    {                                                                               // а по y - центр шарика находится ниже чем низ блока              
        return BallCollisionLeftBottomCorner(ball);
    }    
    // Столкновение с левым верхним углом
    else if (ballCenterX < blockLeftX && ballCenterY < blockTopY)                   // По х - центр шарика находится левее чем левый край блока                                                             
    {                                                                               // По y - центр шарика находится выше чем верх блока         
        return BallCollisionLeftTopCorner(ball);
    }

    // Столкновение с правм верхним углом
    else if (ballCenterX > blockRightX && ballCenterY < blockTopY)                 // По х - центр шарика находится правее чем правый край блкоа                         
    {                                                                              // По y - центр шарика находится выше чем верх блока               
        return BallCollisionRightTopCorner(ball);
    }

    // Столкновение с парвым нижним углом
    else if (ballCenterX > blockRightX && ballCenterY > blockBottomY)                // По х - центр находится правее чем правый край блока        
    {                                                                                // По у - центр находится ниже чем низ блока         
        return BallCollisionRightBottomCorner(ball);
    }

    // Столкновение с низом
    else if (ballCenterX > blockLeftX && ballCenterX < blockRightX                   // Если по х находимся в диапазоне блока
        && ballBottomY > blockBottomY)                                               // И по y находимся ниже нижнего края
    {        
        return BallCollisionBottomWall(ball);
    }

    // Столкновение с верхом
    else if (ballCenterX > blockLeftX && ballCenterX < blockRightX                       // Если по х находимся в диапазоне блока
        && ballTopY < blockTopY)                                                         // И по y находимся выше верхнего края края
    {        
        return BallCollisionTopWall(ball);
    }

    // Если находимся с левоой стороны
    else if (ballCenterY > blockTopY && ballCenterY < blockBottomY                      // Если по y находимся в диапазоне платформы
        && ballLeftX < blockLeftX)                                                      // И по х находимся слева
    {        
        return BallCollisionLeftWall(ball);
    }

    // Если находимся с правой стороны
    else if (ballCenterY > blockTopY && ballCenterY < blockBottomY                      // Если по y находимся в диапазоне платформы
        && ballRightX > blockRightX)                                                    // И по х находимся справа
    {        
        return BallCollisionRightWall(ball);
    }
    else
    {
        return ball.GetAngleUnitCircle();                                                          // Неизвестная ситуация, шарик остановится.
    }
}


Vector2f Block::BallCollisionRightBottomCorner(Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение
    
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();
    // Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
        angleUnitCircle.x = 0.9;                                   // Отлетаем налево
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else 
    {
        if (angleUnitCircle.y < 0)
        {
            ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
            angleUnitCircle.y = -angleUnitCircle.y;                 // Отражаемся по y только вниз                    
        }
        else
        {
            ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
            angleUnitCircle.x = -angleUnitCircle.x;                 // Отражаемся только по х
        }
        
    }  
    

    return angleUnitCircle;
}

Vector2f Block::BallCollisionLeftBottomCorner(Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение по 
    

    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    //Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
        angleUnitCircle.x = -0.9;                                   //отлетаем налево
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else
    {
        if (angleUnitCircle.y < 0)
        {
            ball.setPosition(ball.getPosition().x, this->GetRect().top + this->GetRect().height);
            angleUnitCircle.y = -angleUnitCircle.y;                 // Отражаемся по y только вниз                    
        }
        else
        {
            ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
            angleUnitCircle.x = -angleUnitCircle.x;                 // Отражаемся только по х
        }

    }   

    return angleUnitCircle;
}

Vector2f Block::BallCollisionRightTopCorner(Ball& ball)
{
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    //Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        // Если попали в этот угол то устанавливаемся в максимально возможное положение
        ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
        angleUnitCircle.x = 0.9;                                   //отлетаем налево
        angleUnitCircle.y = -1* sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else
    {
        if (angleUnitCircle.y > 0)
        {            
            ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
            angleUnitCircle.y = -angleUnitCircle.y;                 // Отражаемся по y                    
        }
        else
        {            
            ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
            angleUnitCircle.x = -angleUnitCircle.x;                 // Отражаемся только по х
        }

    }   

    return angleUnitCircle;
}

Vector2f Block::BallCollisionLeftTopCorner(Ball& ball)
{
    
    
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    //Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        // Если попали в этот угол то устанавливаемся в максимально возможное положение
        ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
        angleUnitCircle.x = -0.9;                                   //отлетаем налево
        angleUnitCircle.y = -1 * sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else
    {
        if (angleUnitCircle.y > 0)
        {
            ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
            angleUnitCircle.y = -angleUnitCircle.y;                 // Отражаемся по y только вниз                    
        }
        else
        {
            ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
            angleUnitCircle.x = -angleUnitCircle.x;                 // Отражаемся только по х
        }

    }   

    return angleUnitCircle;
}

Vector2f Block::BallCollisionBottomWall(Ball& ball)
{
    // Если попали в это место то устанавливаемся в максимальное положение
    ball.setPosition(ball.getPosition().x, this->GetRect().top + BLOCK_HEIGHT);
   
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.y = abs(angleUnitCircle.y);                 //отражаемся по y только вниз                    
      

    return angleUnitCircle;
}

Vector2f Block::BallCollisionTopWall(Ball& ball)
{
    // Если попали в это место то устанавливаемся в максимально возможное положение
    ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);

    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.y = -1 * abs(angleUnitCircle.y);                 //отражаемся по y только вверх                    

    return angleUnitCircle;
}

Vector2f Block::BallCollisionLeftWall(Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение
    ball.setPosition(this->GetRect().left-BLUE_BALL_WIDTH, ball.getPosition().y);

    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.x = -1 * abs(angleUnitCircle.x);                         //отражаемся по х
    
   

    return angleUnitCircle;
}

Vector2f Block::BallCollisionRightWall(Ball& ball)
{    
    // Если попали в это место то устанавливаемся в максимально возможное положение
    ball.setPosition(this->GetRect().left + BLOCK_WIDTH, ball.getPosition().y);

    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.x = -angleUnitCircle.x;                         //отражаемся по х
    
    return angleUnitCircle;
}