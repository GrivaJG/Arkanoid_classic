#pragma once

#include "Border.h"
#include <sstream>

#pragma warning(disable : 4996); //�������� �� ���������� ������ text.setColor(Color::Yellow)

class Menu //������� ��������
{
private:
	Menu();

	unsigned score = 0;
	int lives = 0;
	unsigned level = 1;


	//��������� ������
	Font font;

	Text text_startgame;
	Text text_score;
	Text text_level;
	Text text_lives;
	Text text_game_over;


public:
	Menu(Menu& otner) = delete;
	void operator=(const Menu&) = delete;

	static Menu& GetInstance() //����������� ������� �������������
	{
		static Menu menu_;
		return menu_;
	}

	void SetCountScore(int x) { score += x; }
	const unsigned& GetCountScore() const { return score; }

	void SetCountlives(int x) { lives += x; }
	const int& GetCountlives() const { return lives; }

	void Setlevel(int x) { level += x; }
	const unsigned& Getlevel() const { return level; }

	void CreateStartMenu(Image& image, RenderWindow& window, Platform& platform, Balls& ball, Border& board);
	void CreateMenu();
};