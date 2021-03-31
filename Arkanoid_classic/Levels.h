

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





public:
    Levels();
    ~Levels();

    int StartGame(RenderWindow& window);

};

#endif