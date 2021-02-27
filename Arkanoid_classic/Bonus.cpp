
#include "Bonus.h"


Bonus::Bonus(Image& img, BlockType blockType, Vector2f startPosition) : GameObject(img), _bonusType(blockType)
{
    this->setTexture(_texture);
    this->setPosition(startPosition);
   
    switch (_bonusType)
    {
    case BLUE:
        this->setTextureRect(sf::IntRect(BLUE_BONUS_LEFT, BLUE_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case GREEN:
        this->setTextureRect(sf::IntRect(GREEN_BONUS_LEFT, GREEN_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;    
    case PINK:
        this->setTextureRect(sf::IntRect(PINK_BONUS_LEFT, PINK_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case PURPLE:
        this->setTextureRect(sf::IntRect(PURPLE_BONUS_LEFT, PURPLE_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case RED:
        this->setTextureRect(sf::IntRect(RED_BONUS_LEFT, RED_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case YELLOW:
        this->setTextureRect(sf::IntRect(YELLOW_BONUS_LEFT, YELLOW_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    default:
        throw ("invalid argument bonusType");
        break;
    }
}

void Bonus::Move(float time)
{
    this->move(0, _speedFall * time);
}

void Bonus::CollisionWithPlatform(ConcretePlatform* platform, std::list<Ball*>& ball)
{
    switch (_bonusType)
    {
    case BLUE:
        ChangePlatform(platform); // ����������� ��� ��������� ���������
        break;
    case RED:
//        LaserOnBoard(platform);  // ������������� ����� �� ���������
        break;
        
    case PURPLE:
        MultipleBall(ball); // �� ������� ������ � ���� �������� ��� ��� ������
        break;
    case PINK:
        ChangeSpeedBall(ball); // �������� ��� ��������� �����(�)
        break;
    case GREEN:
        CatchBall(ball);    // ���� ����� �� ������ ������� ����, �� ������������� � ���������
        break;
    case YELLOW:
        AddLive();		// ���� ����� ��������� ���� ����� ������
        break;
    default:
        throw("invalid _bonusType");
        break;
    }
}

 
 





void Bonus::MultipleBall(std::list<Ball*>& ball)
{
    std::list<Ball*>::iterator bl;
    std::list<Ball*> ballTemp;
    std::list<Ball*>::iterator blTmp;

    Vector2f angleUnitCircleTemp;

    blTmp = ballTemp.begin();
    
    for (bl = ball.begin(); bl != ball.end(); bl++)
    {        
        Ball* temp1 = new Ball(this->_image, (*bl)->GetSpeed(), false);
        Ball* temp2 = new Ball(this->_image, (*bl)->GetSpeed(), false);

        temp1->setPosition((*bl)->getPosition());
        temp2->setPosition((*bl)->getPosition());

        angleUnitCircleTemp.x = (*bl)->GetAngleUnitCircle().x + 0.2;
        angleUnitCircleTemp.y = sqrt(1 - pow(angleUnitCircleTemp.x, 2));        
        if ((*bl)->GetAngleUnitCircle().y < 0)
        {
            angleUnitCircleTemp.y = -angleUnitCircleTemp.y;
        }
        temp1->SetAngleUnitCircle(angleUnitCircleTemp);

        ballTemp.push_back(temp1);

        angleUnitCircleTemp.x = (*bl)->GetAngleUnitCircle().x - 0.2;
        angleUnitCircleTemp.y = sqrt(1 - pow(angleUnitCircleTemp.x, 2));
        if ((*bl)->GetAngleUnitCircle().y < 0)
        {
            angleUnitCircleTemp.y = -angleUnitCircleTemp.y;
        }
        temp2->SetAngleUnitCircle(angleUnitCircleTemp);

        ballTemp.push_back(temp2);       
    }

    std::cout << "all OK" << std::endl;

    for (blTmp = ballTemp.begin(); blTmp != ballTemp.end();)
    {        
        ball.push_back((*blTmp));
        blTmp = ballTemp.erase(blTmp);
    }
}


void Bonus::ChangePlatform(ConcretePlatform* platform)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());

    if (platform->GetSizePlatform() < 2 || platform->GetSizePlatform() > 2)
    {
        platform->ChangePlatform(mediumPlatform);
    }
    else if (mersenne() % 2 == 0)
    {
        platform->ChangePlatform(smallPlatform);
    }
    else
    {
        platform->ChangePlatform(largePlatform);
    }
}

void Bonus::LaserOnBoard(ConcretePlatform* platform)
{

}

void Bonus::ChangeSpeedBall(std::list<Ball*>& ball)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::list<Ball*>::iterator it;
    it = ball.begin();
    int rand = mersenne() % 2;
    for (it = ball.begin(); it != ball.end(); it++)
    {
        if (rand == 0)
        {
            (*it)->SetSpeedSlow();
        }
        else
        {
            (*it)->SetSpeedFast();
        }
    }
    
}

void Bonus::CatchBall(std::list<Ball*>& ball)
{    

}

void Bonus::AddLive()
{
    Menu::GetInstance().SetCountlives(1);
}