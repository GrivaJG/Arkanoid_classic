
#include "Config.h"
#include "Menu.h"

#include "Bonus.h"

Bonus::Bonus(Image& img, BlockType block_type, Vector2f start_position) : GameObject(img), m_bonus_type(block_type)
{
    this->setTexture(m_texture);
    this->setPosition(start_position);
   
    switch (m_bonus_type)
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
        throw ("invalid argument bonus_type");
        break;
    }
}

void Bonus::Move(float time)
{
    this->move(0, m_speed_fall * time);
}

void Bonus::CollisionWithPlatform(ConcretePlatform* platform, std::vector<Ball*>& ball)
{
    switch (m_bonus_type)
    {
    case BLUE:
        ChangePlatform(platform); // Random uvelichivaem ili umenshaem platformu
        break;
    case RED:
        LaserOnBoard(platform);   // Add 10 bullets
        break;
        
    case PURPLE:
        MultipleBall(ball);       // Iz kazhdogo sharika v igre viletaet eshe dva sharika
        break;
    case PINK:
        ChangeSpeedBall(ball);    // Uskoryaem ili zamedlyaem sharik(i)
        break;
    case GREEN:
        CatchBall(ball);          // Esly sharik na ecrane ostalsya odin on prikleevaetsya k platforme
        break;
    case YELLOW:
        AddLive();		          // add 1 lives
        break;
    default:
        throw("invalid _bonusType");
        break;
    }
}

void Bonus::MultipleBall(std::vector<Ball*>& ball)
{
    std::vector<Ball*>::iterator bl;
    std::vector<Ball*> ball_temp;
    std::vector<Ball*>::iterator bl_tmp;

    Vector2f angle_unit_circle_temp;

    bl_tmp = ball_temp.begin();
    
    for (bl = ball.begin(); bl != ball.end(); bl++)
    {        
        Ball* temp1 = new Ball(this->m_image, (*bl)->GetSpeed(), false);
        Ball* temp2 = new Ball(this->m_image, (*bl)->GetSpeed(), false);

        temp1->setPosition((*bl)->getPosition());
        temp2->setPosition((*bl)->getPosition());

        if ((*bl)->GetAngleUnitCircle().x > 0.75)
        {
            angle_unit_circle_temp.y = (*bl)->GetAngleUnitCircle().y + 0.2;
            angle_unit_circle_temp.x = sqrt(1 - pow(angle_unit_circle_temp.y, 2));

            if ((*bl)->GetAngleUnitCircle().x < 0)
            {
                angle_unit_circle_temp.x = -abs(angle_unit_circle_temp.x);
            }
            else
            {
                angle_unit_circle_temp.x = abs(angle_unit_circle_temp.x);
            }
        }
        else
        {
            angle_unit_circle_temp.x = (*bl)->GetAngleUnitCircle().x + 0.2;
            angle_unit_circle_temp.y = sqrt(1 - pow(angle_unit_circle_temp.x, 2));

            if ((*bl)->GetAngleUnitCircle().y < 0)
            {
                angle_unit_circle_temp.y = -abs(angle_unit_circle_temp.y);
            }
            else
            {
                angle_unit_circle_temp.y = abs(angle_unit_circle_temp.y);
            }

            
        }
               
        temp1->SetAngleUnitCircle(angle_unit_circle_temp);

        ball_temp.push_back(temp1);

        if ((*bl)->GetAngleUnitCircle().x < -0.75)
        {
            angle_unit_circle_temp.y = (*bl)->GetAngleUnitCircle().y - 0.2;
            angle_unit_circle_temp.x = sqrt(1 - pow(angle_unit_circle_temp.y, 2));

            if ((*bl)->GetAngleUnitCircle().x < 0)
            {
                angle_unit_circle_temp.x = -abs(angle_unit_circle_temp.x);
            }
            else
            {
                angle_unit_circle_temp.x = abs(angle_unit_circle_temp.x);
            }
        }
        else
        {
            angle_unit_circle_temp.x = (*bl)->GetAngleUnitCircle().x - 0.2;
            angle_unit_circle_temp.y = sqrt(1 - pow(angle_unit_circle_temp.x, 2));

            if ((*bl)->GetAngleUnitCircle().y < 0)
            {
                angle_unit_circle_temp.y = -abs(angle_unit_circle_temp.y);
            }
            else
            {
                angle_unit_circle_temp.y = abs(angle_unit_circle_temp.y);
            }
        }
        
        temp2->SetAngleUnitCircle(angle_unit_circle_temp);

        ball_temp.push_back(temp2);       
    }    

    for (bl_tmp = ball_temp.begin(); bl_tmp != ball_temp.end();)
    {        
        ball.push_back((*bl_tmp));
        bl_tmp = ball_temp.erase(bl_tmp);
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
    platform->GetInstance()->SetBullets();
}

void Bonus::ChangeSpeedBall(std::vector<Ball*>& ball)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<Ball*>::iterator it;
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

void Bonus::CatchBall(std::vector<Ball*>& ball)
{    
    std::vector<Ball*>::iterator bl;
    
    for (bl = ball.begin(); bl != ball.end(); bl++)
    {
        (*bl)->SetFlagCatch(true);
        (*bl)->SetCatchCounter();
    }
}

void Bonus::AddLive()
{
    Menu::GetInstance().SetCountlives(1);
}