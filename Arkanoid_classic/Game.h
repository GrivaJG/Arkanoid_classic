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

    bool GetFlagBallMove() { return _flagBallMove; }            //is the ball in motion?
    void SetFlagBallMove(bool flag) { _flagBallMove = flag; }

    void StartGame();

private:
    Game();

    Image m_image;

    Border _board;
    ConcretePlatform* _platform;


    unsigned _level;                // Current level number 

    std::list<class Block*> _block;


    std::list<class Bonus*> _bonus;


    std::list<class Ball*> _ball;
    bool _flagBallMove;				



    std::list<class Bullets*> _bullets;

};







