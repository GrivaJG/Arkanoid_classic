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

    bool GetFlagBallMove() { return m_flag_ball_move; }            //is the ball in motion?
    void SetFlagBallMove(bool flag) { m_flag_ball_move = flag; }

    void StartGame();

   

private:
    Game();

    Image m_image;

    Border m_board;                  // Border Map
    ConcretePlatform* m_platform;   

    std::list<class Block*> m_blocks;
    std::list<class Bonus*> m_bonuses;
    std::list<class Ball*> m_balls;
    std::list<class Bullets*> m_bullets;

    unsigned m_level;                // Current level number 
    bool m_flag_ball_move;



    

    void GameLoop(RenderWindow& window);                    //Base game logic
    void GameObjectInit();

};







