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

    Border _board;
    ConcretePlatform* _platform;


    unsigned _level;                // Current level number 

    std::list<Block*> _block;


    std::list<Bonus*> _bonus;


    std::list<Ball*> _ball;
    bool _flagBallMove;				 // Флаг запуска шарика



    std::list<Bullets*> _bullets;





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










};

