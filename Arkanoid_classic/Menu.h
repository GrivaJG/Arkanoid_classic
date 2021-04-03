#pragma once

#include "Config.h"
#include "Border.h"
#include "Platform.h"


#pragma warning(disable : 4996); // Disable warning for text.setColor(Color::Yellow)

class Menu // Simple Singleton
{
public:
	Menu(Menu& otner) = delete;
	void operator=(const Menu&) = delete;

	static Menu& GetInstance() // Static initialization function
	{
		static Menu menu_;
		return menu_;
	}

	void SetCountScore(int x) { m_score += x; }
	const unsigned& GetCountScore() const { return m_score; }

	void SetCountlives(int x) { m_lives += x; }
	const int& GetCountlives() const { return m_lives; }

	void SetScoreRecord() { if (m_score > m_score_record) m_score_record = m_score; }
	const unsigned GetScoreRecord() { return m_score_record; }

	void ResetCombo() { m_combo = 1; }
	void IncreaseCombo() { m_combo += 1; }
	const unsigned GetCombo() { return m_combo; }

	void CreateStartMenu(RenderWindow& window);
	void CreateMenu(RenderWindow& window, unsigned level);
	void CreateStopGame(RenderWindow& window, std::vector<Block*>& blocks, Border& board, ConcretePlatform* platform);
	void CreateEndGame(RenderWindow& window, std::vector<Block*>& blocks, Border& board, ConcretePlatform* platform);
	void PlayerInit() { m_score = 0; m_lives = 3; }

	void CreateLevelSplashScreen(RenderWindow& window, Border& board, unsigned level);

private:
	Menu();

	uint32_t m_score_record = 0;
	uint32_t m_score = 0;
	int32_t m_lives = 0;
	

	uint8_t m_combo = 1;
	
	// Texts and Fonts
	Font m_font;

	Text m_text_start_game;
	Text m_text_score;
	Text m_text_level;
	Text m_text_lives;	
	Text m_text_stop_game;
	Text m_text_congratulations;
};