
#ifndef GAME_H_
#define GAME_H_

#include "Config.h"
#include "Border.h"
#include "Levels.h"
#include "Platform.h"

class Block;
class CollisionManager;

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

    std::vector<class Block*> m_blocks;
    std::vector<class Bonus*> m_bonuses;
    std::vector<class Ball*> m_balls;
    std::vector<class Bullets*> m_bullets;

    uint16_t m_level;                      // Current level number 
    uint16_t m_total_levels;
    bool m_flag_ball_move;

    Levels m_levels;
    CollisionManager* m_collision_manager;
    
    
    uint8_t GameLoop(RenderWindow& window);   //Base game logic
    void GameObjectInit();
    void GetTotalLevels();
};

#endif; //GAME_H_






