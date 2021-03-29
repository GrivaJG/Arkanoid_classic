#pragma once




class Game // Simple Singleton
{

public:
	Game(Game& otner) = delete;
	void operator=(const Game&) = delete;

	static Game& GetInstance() // static initialization function 
	{
		static Game game_;
		return game_;
	}

private:
    Game() { m_image.loadFromFile(IMGPATH); }

    Image m_image;

    unsigned _level;                // Current level number 

    //Border screen
    Border _board;

    // Game Objects
    std::list<Block*> _block;
    std::list<Bonus*> _bonus;
    std::list<Bullets*> _bullets;
    std::list<Ball*> _ball;
    ConcretePlatform* _platform;
        
    bool _flagBallMove;				 // Active when Ball in Move

    void GameInit();                 // Initialization all game objects
    int InitLevel(int lvl);          // Create level

    int BlockSetPosition(int startPositionTop, int startPostitionLeft, int positionX, int positionY); // ?????

    int StartGame(RenderWindow& window);










};

