
#include "Menu.h"
#include "Ball.h"
#include "Block.h"
#include "Platform.h"
#include "Bonus.h"
#include "Bullets.h"
#include "Game.h"
#include "MusicAndSounds.h"
#include "EventHandler.h"



void EventHandler::CollisionBallWithLeftWall(Ball& ball)
{
	ball.CollisionWithLeftWall();
	MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
}

void EventHandler::CollisionBallWithRightWall(Ball& ball)
{
	ball.CollisionWithRightWall();
	MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
}

void EventHandler::CollisionBallWithTop(Ball& ball)
{
	ball.CollisionWithTop();
	MusicAndSounds::GetInstance().BallBounceOfBorderMapPlay();
}

void EventHandler::CollisionBallWithPlatform(Ball& ball, ConcretePlatform* platform)
{
    Menu::GetInstance().ResetCombo();

    if (ball.GetFlagCatch() && Ball::GetBallCount() == 1)
    {
        if (!ball.GetFlagBallCatchPosition())
        {
            MusicAndSounds::GetInstance().BallCatchPlay();

            ball.SetCatchPositionX(ball.getPosition().x - platform->GetInstance()->GetRect().left);
            ball.SetFlagBallCatchPosition(true);
            ball.DecreaseCatchCounter();
        }

        ball.setPosition(platform->GetInstance()->GetRect().left + ball.GetCatchPositionX(), platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT + 1);
    }
    else
    {
        MusicAndSounds::GetInstance().BallBounceOfPlatformPlay();
        ball.SetAngleUnitCircle(platform->GetInstance()->CollisionWithBall(ball));

        if (ball.GetCatchCounter() > 0)
        {
            ball.SetFlagCatch(true);
        }
    }
}

void EventHandler::CollisionBallWithBlock(Ball& ball, Block& block, std::list<Bonus*>& bonuses)
{
    Menu::GetInstance().SetCountScore(10 * Menu::GetInstance().GetCombo());
    Menu::GetInstance().IncreaseCombo();

    MusicAndSounds::GetInstance().BallBounceOfBlockPlay();

    ball.SetAngleUnitCircle(block.BallCollision(ball));
    if (block.GetFlagBonus())
    {
        bonuses.push_back(new Bonus(block.GetImage(), block.GetBlockType(), Vector2f(block.GetRect().left + block.GetRect().width / 2 - BONUS_WIDTH / 2, block.getPosition().y)));
    }    
}

void EventHandler::CollisionBallWithBottom(Ball& ball, ConcretePlatform* platform)
{
    Game::GetInstance().SetFlagBallMove(false);
    ball.SetFlagInit(true);
    ball.ResetCatch();
    ball.ResetSpeed();    

    Menu::GetInstance().SetCountlives(-1);
    MusicAndSounds::GetInstance().BallFallPlay();

    platform->GetInstance()->ReSetBullets();
    platform->ChangePlatform(mediumPlatform);
}

void EventHandler::CollisionPlatformWithBonus(ConcretePlatform* platform, Bonus& bonus, std::list<Ball*>& balls)
{
    MusicAndSounds::GetInstance().PlatformCollBonusPlay();
    bonus.CollisionWithPlatform(platform, balls);   
}

void EventHandler::CollisionBulletsWithTop(Bullets& bullet)
{
    MusicAndSounds::GetInstance().BulletsHitBorderMapPlay();
}

void EventHandler::CollisionBulletsWithBlock(Bullets& bullet, Block& block, std::list<Bonus*>& bonuses)
{
    MusicAndSounds::GetInstance().BulletsHitBlockPlay();
    if (block.GetFlagBonus())
    {
        bonuses.push_back(new Bonus(block.GetImage(), block.GetBlockType(), Vector2f(block.GetRect().left + block.GetRect().width / 2 - BONUS_WIDTH / 2,
            block.getPosition().y)));
    }
}
