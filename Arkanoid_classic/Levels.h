

#ifndef _LEVELS_H
#define _LEVELS_H

class Block;
class Levels
{
public:
    Levels(Image& image) : m_image(image) {}

    void InitLevel(int lvl, std::vector<class Block*>& blocks);

private:

    Image& m_image;

    int BlockSetPosition(int startPositionTop, int startPositionLeft, int positionX, int positionY, std::vector<class Block*>& blocks);
};

#endif