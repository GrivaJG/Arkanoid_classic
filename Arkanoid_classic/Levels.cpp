
#include "Config.h"
#include "Block.h"
#include "Levels.h"

void Levels::InitLevel(int lvl, std::vector<Block*>& blocks)
{
    std::ifstream file(LEVEL_CREATOR_PATH);
    if (file.fail())
    {
        std::cout << "File lvl_creator is not found" << std::endl;
        system("pause");
        exit(-1);
    }

    std::ostringstream level;
    level << lvl;
    std::string levelForCreate = "Level: " + level.str();
    
    std::string stringOfFile;

    while (!file.eof())
    {
        std::getline(file, stringOfFile);
        if (stringOfFile == levelForCreate)
        {
            int16_t positionX = 0;
            int16_t positionY = 0;
            int16_t startPositionTop = 0;
            int16_t startPositionLeft = 0;

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
                        blocks.push_back(new Block(m_image, YELLOW, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'G' && stringOfFile[i + 2] == 'R')
                    {
                        blocks.push_back(new Block(m_image, GREEN, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'P' && stringOfFile[i + 2] == 'I')
                    {
                        blocks.push_back(new Block(m_image, PINK, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'P' && stringOfFile[i + 2] == 'U')
                    {
                        blocks.push_back(new Block(m_image, PURPLE, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'R' && stringOfFile[i + 2] == 'E')
                    {
                        blocks.push_back(new Block(m_image, RED, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'B' && stringOfFile[i + 2] == 'L')
                    {
                        blocks.push_back(new Block(m_image, BLUE, true));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 3;
                    }

                    else if (stringOfFile[i] == 'Y' && stringOfFile[i + 1] == 'E')
                    {
                        blocks.push_back(new Block(m_image, YELLOW));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'G' && stringOfFile[i + 1] == 'R')
                    {
                        blocks.push_back(new Block(m_image, GREEN));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'P' && stringOfFile[i + 1] == 'I')
                    {
                        blocks.push_back(new Block(m_image, PINK));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'P' && stringOfFile[i + 1] == 'U')
                    {
                        blocks.push_back(new Block(m_image, PURPLE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'R' && stringOfFile[i + 1] == 'E')
                    {
                        blocks.push_back(new Block(m_image, RED));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'B' && stringOfFile[i + 1] == 'L')
                    {
                        blocks.push_back(new Block(m_image, BLUE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
                        i += 2;
                    }

                    else if (stringOfFile[i] == 'O' && stringOfFile[i + 1] == 'R')
                    {
                        blocks.push_back(new Block(m_image, ORANGE));
                        positionX = BlockSetPosition(startPositionTop, startPositionLeft, positionX, positionY, blocks);
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
}

int Levels::BlockSetPosition(int startPositionTop, int startPositionLeft, int positionX, int positionY, std::vector<Block*>& blocks)
{
    std::vector<Block*>::iterator blk;
    blk = blocks.end();
    blk--;
    (*blk)->setPosition(startPositionLeft + positionX * (BLOCK_WIDTH + 1), startPositionTop + positionY * (BLOCK_HEIGHT + 1));
    positionX++;
    return positionX;
}









