
#ifndef GAME_H_
#define GAME_H_

class Border;
class ConcretePlatform;
class Ball;
class Block;
class Bonus;
class Bullets;
class CollisionManager;
class Levels;

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

    bool GetFlagBallMove() { return m_flag_ball_move; }            
    void SetFlagBallMove(bool flag) { m_flag_ball_move = flag; }

    void StartGame();   

private:
    Game();
    ~Game();

    Image m_image;

    Border m_board;                        // Border Map
    ConcretePlatform* m_platform;   
    
    std::list<Block*> m_blocks;
    std::list<class Bonus*> m_bonuses;
    std::list<class Ball*> m_balls;
    std::list<class Bullets*> m_bullets;

    unsigned m_level;                      // Current level number 
    bool m_flag_ball_move;

    CollisionManager* m_collision_manager;
    Levels m_levels;
    
    int GameLoop(RenderWindow& window);   //Base game logic
    void GameObjectInit();

};

#endif; //GAME_H_






