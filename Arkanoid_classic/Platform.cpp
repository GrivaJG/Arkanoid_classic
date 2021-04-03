
#include "Ball.h"
#include "Platform.h"
#include "Config.h"
#include "MusicAndSounds.h"

//-------------------------------------------------------------------------Platform
// Move platform
void Platform::Move(const float speed, const float time)
{
    this->move(speed * time, 0);
}

// Collision platform with ball
Vector2f Platform::CollisionWithBall(Ball& ball) // Peresechenie platformi s sharikom
{    
    float collisionLocation = CollisionLocation(ball);

    // Esli center sharika po koordinate x nahoditsya levee platformi 
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(ball);
    }
    // Esli center charika po koordinate x nahodytsya na levom krae
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(ball);
    }
    // Esli center charika po koordinate x nahodytsya po seredine megdu levim i pravim kraem
    else if (collisionLocation < GetRect().width - 8)
    {
        return this->BallCollisionStandart(ball);
    }
    // Если центр шарика по координате х находится на правом крае
    else if (collisionLocation < GetRect().width)
    {
        return this->BallCollisionRightEdge(ball);
    }
    // Esli center charika po koordinate x nahodytsya pravee platformi
    else
    {
        return this->BallCollisionRightWall(ball);
    }

}

Vector2f Platform::BallCollisionLeftEdge(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    // Esli prizemlilis na platformu pod pramim uglom
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x > 0) // else esli letim sleva napravo i udaryaemsya v leviy ugol to dolgni otrazitsya obratno
    {
        angleUnitCircle.x = -angleUnitCircle.x;        // otragaemsya po x
        angleUnitCircle.y = -angleUnitCircle.y;        // otragaemsya po y
    }
    else if (angleUnitCircle.x < 0) // else esli letim sprava nalevo, to dolgni uletet pod bOlshim uglom
    {
        angleUnitCircle.x = -0.9;                                 // otragaemsya po x
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); 
        angleUnitCircle.y = -angleUnitCircle.y;                   // otragaemsya po y
    }

    return angleUnitCircle;
    

}

Vector2f Platform::BallCollisionRightEdge(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    // Esli prizemlilis na platformu pod pramim uglom
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = 0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x < 0) // else esli letim sprava nalevo i udaryaemsya v praviy ugol to dolgni otrazitsya obratno
    {
        angleUnitCircle.x = -angleUnitCircle.x;        // otragaemsya po x
        angleUnitCircle.y = -angleUnitCircle.y;        // otragaemsya po y              
    }
    else if (angleUnitCircle.x > 0) // Else esli letim sleva napravo, to dolgni uletet pod bolshim uglom
    {
        angleUnitCircle.x = 0.9;                                 // otragaemsya po x
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;                      // otragaemsya po y 
    }

    return angleUnitCircle;


}

Vector2f Platform::BallCollisionStandart(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    // Esli po x prakticheski ne smeshamesya i popadayem v centralnuu chast platformi, to dolgni uletet libo vparvo, libo vlevo v zavisimosty  ot
    // sostoyaniya peremennoi change_angel
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
    // Else prosto menyaem napravlenie poleta po y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f Platform::BallCollisionLeftWall(Ball& ball)
{
    // Ne daem shariku proletet skvoz platformu
    ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.x = -1 * abs(angleUnitCircle.x); // odnoznachno letim tolko vlevo ot platformi, po y prodolgaem letet kak leteli
    return angleUnitCircle;
}

Vector2f Platform::BallCollisionRightWall(Ball& ball)
{
    // Ne daem shariku zaletet vnutr platformi
    ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    angleUnitCircle.x = abs(angleUnitCircle.x); // odnoznachno letim vpravo ot platformi
    return angleUnitCircle;
}

// Opredelyaem v kakoe mesto platformi popal sharik
float Platform::CollisionLocation(Ball& ball)
{
    return ball.GetRect().left + ( ball.GetRect().width / 2 ) - this->GetRect().left;
}

//-------------------------------------------------------------------------MediumPlatform
MediumPlatform::MediumPlatform(Image& img) : Platform(img)
{       
    this->setTexture(m_texture);
    this->setTextureRect(IntRect(MEDIUM_PLATFORM_LEFT, MEDIUM_PLATFORM_TOP, MEDIUM_PLATFORM_WIDTH, MEDIUM_PLATFORM_HEIGHT));        
}

//--------------------------------------------------------------------------SmallPlatform
SmallPlatform::SmallPlatform(Image& img) : Platform(img)
{   
    this->setTexture(m_texture);
    this->setTextureRect(IntRect(SMALL_PLATFORM_LEFT, SMALL_PLATFORM_TOP, SMALL_PLATFORM_WIDTH, SMALL_PLATFORM_HEIGHT));    
}

//--------------------------------------------------------------------------LargePlatform
LargePlatform::LargePlatform(Image& img) : Platform(img)
{   
    this->setTexture(m_texture);
    this->setTextureRect(IntRect(LARGE_PLATFORM_LEFT, LARGE_PLATFORM_TOP, LARGE_PLATFORM_WIDTH, LARGE_PLATFORM_HEIGHT));    
}

Vector2f LargePlatform::CollisionWithBall(Ball& ball)
{
    float collisionLocation = this->CollisionLocation(ball);
    // Esli centr sharika po koordinate x nahoditsya levee platformi
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(ball);
    }
    // Esli center sharika po coordinate x nahoditsya na levom krae
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(ball);
    }
    // Esli popali v krai platformi osnovnoi zoni, no ne v sam ugol
    else if (collisionLocation < 16)
    {
        return this->BallCollisionLeftEdgePlus(ball);
    }
    // Esli popali v livuu chast
    else if (collisionLocation < 58)
    {
        return this->BallCollisionStandart(ball);
    }
    // Esli popali v samii center
    else if (collisionLocation < 72)
    {
        return this->BallCollisionCenter(ball);
    }

    // Esli popali v pravuu chast
    else if (collisionLocation < this->GetRect().width - 16)
    {
        return this->BallCollisionStandart(ball);
    }
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionRightEdgePlus(ball);
    }
    // Esli center sharika po koordinate x nahoditsya na pravom kraeЕсли центр шарика по координате х находится на правом крае
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(ball);
    }
    // Esli center sharika po koordinate x nahoditsya pravee platformi
    else
    {
        return this->BallCollisionRightWall(ball);
    }
}

Vector2f LargePlatform::BallCollisionLeftEdgePlus(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); // Esli peresekli platformu, to vitalkivaem sharik iz platformi
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) // Esli po x prakticheski ne smeshaemsya i popadaem v levii krai, to dolgni slegka izmenit svou traektoriu
    {
        angleUnitCircle.x += -0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x < 0) // Else esli letim sprava nalevo i udaryaemsya v livii ugol, to dolgni otrazitsya nalevo na chut bolshiy ugol
    {
        if (angleUnitCircle.x > -0.8)     // Proveryaem ne sliskom li tupoi ugol, chtobi sharik ne nachal letat parallelno platforme
            angleUnitCircle.x += -0.19;   // Uvelichivaem ugol

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); // Privodim ugol po Y v sootevetstvie s X
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    // Else, esli letim sleva napravo to ne menyaem napravlenie dvigenia po x, a tolko po y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
        
}

Vector2f LargePlatform::BallCollisionRightEdgePlus(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); // Esli peresekly platformu, to vitalkivaem sharik iz platformi
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) // Esli po X prakticheski ne smeshaemsya i popadaem v praviy krai, to dolgni slegka izmenit svou traektoriu
    {
        angleUnitCircle.x += +0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    else if (angleUnitCircle.x > 0) // Else esli letim napravo i udaryaemsya v praviy ugol, to dolgni otrazitsya vpravo na chut bolshiy ugol
    {
        if (angleUnitCircle.x < 0.8)     // Proveryaem ne slishkom li tupoy ugol, chtobi sharik ne nachal letat parallelno platforme
            angleUnitCircle.x += 0.19;   // Uvelichivaem ugol

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); // Privodim ugol po Y v sootvetstvii s X
        angleUnitCircle.y = -angleUnitCircle.y;
    }
    // Else, esli letim sprava nalevo to ne menyaem napravlenie dvigeniya po X, a tolko po Y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f LargePlatform::BallCollisionCenter(Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->GetRect().top - ball.GetRect().height-5); // Esli peresekly platformu, to vitalkivaem sharik iz platformi
    Vector2f angleUnitCircle = ball.GetAngleUnitCircle();

    std::random_device rd;
    std::mt19937 mersenne(rd());
    // Esli po x prakticheski ne smeshamesya i popadayem v centralnuu chast platformi, to dolgni uletet libo vparvo, libo vlevo v zavisimosty  ot
    // sostoyaniya peremennoi change_angel
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
    else // Else esli dvigalis sleva napravo ili sprava nalevo, to nachinaem letet verticalno vverh
    {
        
        angleUnitCircle.x = 0;
        angleUnitCircle.y = -1;        
    }
    return angleUnitCircle;
}




//------------------------------------------------------------Klass kompozicii dlya bistroi podmeni platform



ConcretePlatform::ConcretePlatform(Image& img) : m_image(img)
{
    m_small_platform = new SmallPlatform(m_image);
    m_medium_platform = new MediumPlatform(m_image);
    m_large_platform = new LargePlatform(m_image);
    m_concrete_platform = m_medium_platform;
    m_size_platform = mediumPlatform;
}

ConcretePlatform::~ConcretePlatform()
{    
    delete m_small_platform;
    delete m_medium_platform;
    delete m_large_platform;
   
}


void ConcretePlatform::ChangePlatform(int sizePlatform)
{
    MusicAndSounds::GetInstance().ChangePlatformPlay();
    Vector2f position = m_concrete_platform->getPosition();
    if (sizePlatform <= smallPlatform)
    {
        m_size_platform = smallPlatform;
        m_concrete_platform = m_small_platform;        
    }
    else if (sizePlatform == mediumPlatform)
    {
        m_size_platform = mediumPlatform;
        m_concrete_platform = m_medium_platform;
    }
    else
    {
        m_size_platform = largePlatform;
        m_concrete_platform = m_large_platform;
    }

    m_concrete_platform->setPosition(position);
}

