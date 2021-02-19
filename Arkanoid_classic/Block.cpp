//
//
//#include "Block.h"
//
//
//Block::Block(BlockType blockType, bool bonus)
//{
//    _bonus = bonus;
//    _blockType = blockType;
//    this->setTexture(texture);
//
//    if (_bonus)
//    {
//        switch (_blockType)
//        {
//        case BLUE:
//            this->setTextureRect(sf::IntRect(BLUE_BONUS_BLOCK_LEFT, BLUE_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case GREEN:
//            this->setTextureRect(sf::IntRect(GREEN_BONUS_BLOCK_LEFT, GREEN_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case ORANGE:
//            this->setTextureRect(sf::IntRect(ORANGE_BLOCK_LEFT, ORANGE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case PINK:
//            this->setTextureRect(sf::IntRect(PINK_BONUS_BLOCK_LEFT, PINK_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case PURPLE:
//            this->setTextureRect(sf::IntRect(PURPLE_BONUS_BLOCK_LEFT, PURPLE_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case RED:
//            this->setTextureRect(sf::IntRect(RED_BONUS_BLOCK_LEFT, RED_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case YELLOW:
//            this->setTextureRect(sf::IntRect(YELLOW_BONUS_BLOCK_LEFT, YELLOW_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        default:
//            throw ("invalid argument blockType");
//            break;
//        }
//    }
//    else
//    {
//        switch (_blockType)
//        {
//        case BLUE:
//            this->setTextureRect(sf::IntRect(BLUE_BLOCK_LEFT, BLUE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case GREEN:
//            this->setTextureRect(sf::IntRect(GREEN_BLOCK_LEFT, GREEN_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case ORANGE:
//            this->setTextureRect(sf::IntRect(ORANGE_BLOCK_LEFT, ORANGE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case PINK:
//            this->setTextureRect(sf::IntRect(PINK_BLOCK_LEFT, PINK_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case PURPLE:
//            this->setTextureRect(sf::IntRect(PURPLE_BLOCK_LEFT, PURPLE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case RED:
//            this->setTextureRect(sf::IntRect(RED_BLOCK_LEFT, RED_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        case YELLOW:
//            this->setTextureRect(sf::IntRect(YELLOW_BLOCK_LEFT, YELLOW_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
//            break;
//        default:
//            throw ("invalid argument blockType");
//            break;
//        }
//    }
//
//
//
//    
//    
//}
//
//Vector2f Block::BallCollision(Vector2f angleUnitCircle, Ball& ball)
//{
//    float ballLeftX = ball.GetRect().left;                                        // ����� ���� ������
//    float ballRightX = ball.GetRect().left + ball.GetRect().width;                // ������ ���� �����
//    float ballTopY = ball.GetRect().top;                                          // ���� ������
//    float ballBottomY = ball.GetRect().top + ball.GetRect().height;               // ��� ������
//    float ballCenterX = ball.GetRect().left + (ball.GetRect().width / 2);         // ���������� ������ ������ �� �
//    float ballCenterY = ball.GetRect().top + (ball.GetRect().height / 2);         // ���������� ������ ������ �� y
//
//    float blockBottomY = this->GetRect().top + this->GetRect().height;             // ��� �����
//    float blockTopY = this->GetRect().top;                                         // ���� �����
//    float blockLeftX = this->GetRect().left;                                       // ����� ���� �����
//    float blockRightX = this->GetRect().left + this->GetRect().width;              // ������ ���� �����
//    
//
//
//    // ������������ � ����� ������ �����
//    if (ballCenterX < blockLeftX && ballCenterY > blockBottomY)                     // �� � - ����� ������ ��������� ����� ��� ����� ���� �����,
//    {                                                                               // � �� y - ����� ������ ��������� ���� ��� ��� �����      
//        return BallCollisionLeftBottomCorner(angleUnitCircle, ball);
//    }    
//    // ������������ � ����� ������� �����
//    else if (ballCenterX < blockLeftX && ballCenterY < blockTopY)                   // �� � - ����� ������ ��������� ����� ��� ����� ���� �����                                                             
//    {                                                                               // �� y - ����� ������ ��������� ���� ��� ���� ����� 
//        return BallCollisionLeftTopCorner(angleUnitCircle, ball);
//    }
//
//    // ������������ � ����� ������� �����
//    else if (ballCenterX > blockRightX && ballCenterY < blockTopY)                 // �� � - ����� ������ ��������� ������ ��� ������ ���� �����                         
//    {                                                                              // �� y - ����� ������ ��������� ���� ��� ���� �����         
//        return BallCollisionRightTopCorner(angleUnitCircle, ball);
//    }
//
//    // ������������ � ������ ������ �����
//    else if (ballCenterX > blockRightX && ballCenterY > blockBottomY)                // �� � - ����� ��������� ������ ��� ������ ���� �����        
//    {                                                                                // �� � - ����� ��������� ���� ��� ��� �����   
//        return BallCollisionRightBottomCorner(angleUnitCircle, ball);
//    }
//
//    // ������������ � �����
//    else if (ballCenterX > blockLeftX && ballCenterX < blockRightX                   // ���� �� � ��������� � ��������� �����
//        && ballBottomY > blockBottomY)                                               // � �� y ��������� ���� ������� ����
//    {
//        return BallCollisionBottomWall(angleUnitCircle, ball);
//    }
//
//    // ������������ � ������
//    else if (ballCenterX > blockLeftX && ballCenterX < blockRightX                       // ���� �� � ��������� � ��������� �����
//        && ballTopY < blockTopY)                                                         // � �� y ��������� ���� �������� ���� ����
//    {
//        return BallCollisionBottomWall(angleUnitCircle, ball);
//    }
//
//    // ���� ��������� � ������ �������
//    else if (ballCenterY > blockTopY && ballCenterY < blockBottomY                      // ���� �� y ��������� � ��������� ���������
//        && ballLeftX < blockLeftX)                                                      // � �� � ��������� �����
//    {
//        return BallCollisionBottomWall(angleUnitCircle, ball);
//    }
//
//    // ���� ��������� � ������ �������
//    else if (ballCenterY > blockTopY && ballCenterY < blockBottomY                      // ���� �� y ��������� � ��������� ���������
//        && ballRightX > blockRightX)                                                    // � �� � ��������� ������
//    {
//        return BallCollisionBottomWall(angleUnitCircle, ball);
//    }
//    else
//    {
//        return Vector2f(angleUnitCircle.x*0, angleUnitCircle.y*0);                      // ����������� ��������, ����� �����������.
//    }
//}
//
//
//Vector2f Block::BallCollisionRightBottomCorner(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ���� ���� �� ��������������� � ����������� ��������� ��������� �� 
//    ball.setPosition(this->GetRect().left + BLOCK_WIDTH - BLUE_BALL_WIDTH / 2, this->GetRect().top + BLOCK_HEIGHT);
//
//    //���� ������������ �� ���� ����������� �����
//    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
//    {
//        angleUnitCircle.x = 0.9;                                   //�������� ������
//        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
//    }
//    else 
//    {
//        angleUnitCircle.x = -angleUnitCircle.x;                     //���������� �� �
//        angleUnitCircle.y = abs(angleUnitCircle.y);                 //���������� �� y ������ ����                    
//    }
//    
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//Vector2f Block::BallCollisionLeftBottomCorner(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ���� ���� �� ��������������� � ����������� ��������� ��������� �� 
//    ball.setPosition(this->GetRect().left + BLUE_BALL_WIDTH / 2, this->GetRect().top + BLOCK_HEIGHT);
//
//    //���� ������������ �� ���� ����������� �����
//    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
//    {
//        angleUnitCircle.x = -0.9;                                   //�������� ������
//        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
//    }
//    else
//    {
//        angleUnitCircle.x = -angleUnitCircle.x;                     //���������� �� �
//        angleUnitCircle.y = abs(angleUnitCircle.y);                 //���������� �� y ������ ����                    
//    }
//
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//Vector2f Block::BallCollisionRightTopCorner(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ���� ���� �� ��������������� � ����������� ��������� ��������� �� 
//    ball.setPosition(this->GetRect().left + BLOCK_WIDTH - BLUE_BALL_WIDTH / 2, this->GetRect().top - BLUE_BALL_HEIGHT);
//
//    //���� ������������ �� ���� ����������� �����
//    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
//    {
//        angleUnitCircle.x = 0.9;                                   //�������� ������
//        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
//    }
//    else
//    {
//        angleUnitCircle.x = -angleUnitCircle.x;                         //���������� �� �
//        angleUnitCircle.y = -1 * abs(angleUnitCircle.y);                 //���������� �� y ������ ����                    
//    }
//
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//Vector2f Block::BallCollisionLeftTopCorner(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ���� ���� �� ��������������� � ����������� ��������� ��������� �� 
//    ball.setPosition(this->GetRect().left + BLUE_BALL_WIDTH / 2, this->GetRect().top - BLUE_BALL_HEIGHT);
//
//    //���� ������������ �� ���� ����������� �����
//    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
//    {
//        angleUnitCircle.x = -0.9;                                   //�������� ������
//        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
//    }
//    else
//    {
//        angleUnitCircle.x = -angleUnitCircle.x;                         //���������� �� �
//        angleUnitCircle.y = -1 * abs(angleUnitCircle.y);                 //���������� �� y ������ ����                    
//    }
//
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//Vector2f Block::BallCollisionBottomWall(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ��� ����� �� ��������������� � ������������ ���������
//    ball.setPosition(ball.getPosition().x, this->GetRect().top + BLOCK_HEIGHT);
//   
//    angleUnitCircle.y = abs(angleUnitCircle.y);                 //���������� �� y ������ ����                    
//   
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//Vector2f Block::BallCollisionTopWall(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ��� ����� �� ��������������� � ����������� ��������� ���������
//    ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);
//
//    angleUnitCircle.y = -1 * abs(angleUnitCircle.y);                 //���������� �� y ������ �����                    
//
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//Vector2f Block::BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ���� ���� �� ��������������� � ����������� ��������� ���������
//    ball.setPosition(this->GetRect().left-BLUE_BALL_WIDTH, ball.getPosition().y);
//
//    angleUnitCircle.x = -1 * abs(angleUnitCircle.x);                         //���������� �� �
//    
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//Vector2f Block::BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball)
//{
//    // ���� ������ � ��� ����� �� ��������������� � ����������� ��������� ���������
//    ball.setPosition(this->GetRect().left + BLOCK_WIDTH, ball.getPosition().y);
//
//    angleUnitCircle.x = abs(angleUnitCircle.x);                         //���������� �� �
//
//    if (_bonus)
//    {
//        this->BonusCreate();
//    }
//
//    return angleUnitCircle;
//}
//
//
//void Block::BonusCreate()
//{
//    Vector2f startPosition;
//    startPosition.x = this->GetRect().left + BLOCK_WIDTH / 2 - BONUS_WIDTH / 2;
//    startPosition.y = this->GetRect().top;
//    bonus.push_back(new Bonus(_blockType, startPosition));
//}