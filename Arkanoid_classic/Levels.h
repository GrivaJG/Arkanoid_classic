

#ifndef _LEVELS_H
#define _LEVELS_H

#include "Config.h"
#include "Border.h"
#include "Ball.h"
#include "Platform.h"
#include "Block.h"
#include "Bonus.h"
#include "Bullets.h"





class Levels
{

private:

    Image& _image;

    Border _board;
    ConcretePlatform* _platform;
    

    unsigned _level;                // Текущий номер уровня    
    
    std::list<Block*> _block;
    std::list<Block*>::iterator _blk;

    std::list<Bonus*> _bonus;
    std::list<Bonus*>::iterator _bns;
    

    std::list<Ball*> _ball;
    std::list<Ball*>::iterator _bl;
    bool _flagBallMove;				 // Флаг запуска шарика

    
    
    std::list<Bullets*> _bullets;
    std::list<Bullets*>::iterator _blts;





    // Коллизии
    void CollisionDetecter();
    void BallCollision(); // Всевозможные столкновение шарика с элементами игры
    void PlatformCollision(); // Всевозможные столкновение платформы с элементами игры (кроме столкновения с шариком) 
    void BulletsCollision(); // Все возможные столкновения пули с элементами игры
    void BallFall();          // Шарик упал в spawn зону
    


    // Создание уровней
    void GameInit();
    int InitLevel(int lvl);
    int BlockSetPosition(int startPositionTop, int startPostitionLeft, int positionX, int positionY);

    int StartLevel(RenderWindow& window);

    
    

    







public:
    Levels(Image& img);
    ~Levels();

    int StartGame(RenderWindow& window);

};

#endif