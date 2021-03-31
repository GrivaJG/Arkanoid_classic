
#include "Levels.h"
#include "MusicAndSounds.h"
#include <fstream>
#include <iostream>
#include <cstdlib>




Levels::Levels(Image& img) : _image(img)
{
    
    _platform = new ConcretePlatform(_image);
    _platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    _ball.push_back(new Ball(_image));
    _bl = _ball.begin();
    (*_bl)->setPosition(BALL_START_POSITION);

    _level = 0;    
    _flagBallMove = false;

    MusicAndSounds::GetInstance();

}

















    



//----------------------------------------------------------------Создание уровней

int Levels::InitLevel(int lvl)
{
    std::ifstream file("Config/lvlCreator.ini");
    if (file.is_open())
        std::cout << "FILE is open" << std::endl;

    std::ostringstream level;
    level << lvl;
    std::string levelForCreate = "Level: " + level.str();
    
    std::string stringOfFile;

    while (!file.eof())
    {
        std::getline(file, stringOfFile);
        if (stringOfFile == levelForCreate)
        {
            int positionX = 0;
            int positionY = 0;
            int startPositionTop = 0;
            int startPositionLeft = 0;

            std::getline(file, stringOfFile);

            std::stringstream pos;

            for (size_t i = 14; i < stringOfFile.length(); i++)
            {
                pos << stringOfFile[i];
            }

            pos >> startPositionTop;

            while (stringOfFile != "\0" && !file.eof())
            {

                std::getline(file, stringOfFile);
                std::stringstream ss(stringOfFile);
               
                ss >> startPositionLeft;
                
                for (size_t i = 0; i < stringOfFile.length(); i++)
                {
                    if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'Y' && stringOfFile[i + 2] == 'E')
                    {
                        _block.push_back(new Block(_image, YELLOW, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'G' && stringOfFile[i + 2] == 'R')
                    {
                        _block.push_back(new Block(_image, GREEN, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'P' && stringOfFile[i + 2] == 'I')
                    {
                        _block.push_back(new Block(_image, PINK, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'P' && stringOfFile[i + 2] == 'U')
                    {
                        _block.push_back(new Block(_image, PURPLE, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'R' && stringOfFile[i + 2] == 'E')
                    {
                        _block.push_back(new Block(_image, RED, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'B' && stringOfFile[i + 2] == 'L')
                    {
                        _block.push_back(new Block(_image, BLUE, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'Y' && stringOfFile[i + 1] == 'E')
                    {
                        _block.push_back(new Block(_image, YELLOW));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'G' && stringOfFile[i + 1] == 'R')
                    {
                        _block.push_back(new Block(_image, GREEN));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'P' && stringOfFile[i + 1] == 'I')
                    {
                        _block.push_back(new Block(_image, PINK));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'P' && stringOfFile[i + 1] == 'U')
                    {
                        _block.push_back(new Block(_image, PURPLE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'R' && stringOfFile[i + 1] == 'E')
                    {
                        _block.push_back(new Block(_image, RED));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'L')
                    {
                        _block.push_back(new Block(_image, BLUE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'O' && stringOfFile[i + 1] == 'R')
                    {
                        _block.push_back(new Block(_image, ORANGE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY);
                        i += 2;                        
                    }

                    else if (stringOfFile[i] == 'N' && stringOfFile[i + 1] == 'B')
                    {  
                        positionX++;
                        i += 2;
                    }
                   
                }
                
                positionX = 0;
                positionY++;
                
            }
        }
            
    }
    

    file.close();
    return 0;
}

int Levels::BlockSetPosition(int startPositionTop, int startPositionLeft, int positionX, int positionY)
{
    _blk = _block.end();
    _blk--;
    (*_blk)->setPosition(startPositionLeft + positionX * (BLOCK_WIDTH + 1), startPositionTop + positionY * (BLOCK_HEIGHT + 1));
    positionX++;
    return positionX;
}









