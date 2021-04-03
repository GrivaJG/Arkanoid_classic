
#include "Config.h"
#include "Border.h"

Border::Border()
{
	m_image.loadFromFile(IMGPATH);
	m_texture.loadFromImage(m_image);

	m_left_top_corner.setTexture(m_texture);
	m_left_top_corner.setTextureRect(sf::IntRect(CORNER_LEFT, CORNER_TOP, CORNER_WIDTH, CORNER_HEIGHT));

	m_left_bottom_corner.setTexture(m_texture);
	m_left_bottom_corner.setTextureRect(sf::IntRect(CORNER_LEFT, CORNER_BOTTOM, CORNER_WIDTH, -CORNER_HEIGHT));

	m_right_top_corner.setTexture(m_texture);
	m_right_top_corner.setTextureRect(sf::IntRect(CORNER_RIGHT, CORNER_TOP, -CORNER_WIDTH, CORNER_HEIGHT));

	m_right_bottom_corner.setTexture(m_texture);
	m_right_bottom_corner.setTextureRect(sf::IntRect(CORNER_RIGHT, CORNER_BOTTOM, -CORNER_WIDTH, -CORNER_HEIGHT));

	m_horizontal_top_wall.setTexture(m_texture);
	m_horizontal_top_wall.setTextureRect(sf::IntRect(HORIZONTAL_WALL_LEFT, HORIZONTAL_WALL_TOP, HORIZONTAL_WALL_WIDTH, HORIZONTAL_WALL_HEIGHT));

	m_horizontal_bottom_wall.setTexture(m_texture);
	m_horizontal_bottom_wall.setTextureRect(sf::IntRect(HORIZONTAL_WALL_LEFT, HORIZONTAL_WALL_BOTTOM, HORIZONTAL_WALL_WIDTH, -HORIZONTAL_WALL_HEIGHT));
	
	m_vertical_left_wall.setTexture(m_texture);
	m_vertical_left_wall.setTextureRect(sf::IntRect(VERTICAL_WALL_LEFT, VERTICAL_WALL_TOP, VERTICAL_WALL_WIDTH, VERTICAL_WALL_HEIGHT));

	m_vertical_right_wall.setTexture(m_texture);
	m_vertical_right_wall.setTextureRect(sf::IntRect(VERTICAL_WALL_RIGHT, VERTICAL_WALL_TOP, -VERTICAL_WALL_WIDTH, VERTICAL_WALL_HEIGHT));
}


sf::Sprite Border::GetLeftTopCorner(int posX, int posY)
{
	m_left_top_corner.setPosition(posX, posY);
	return m_left_top_corner;
}

sf::Sprite Border::GetLeftBottomCorner(int posX, int posY)
{
	m_left_bottom_corner.setPosition(posX, posY);
	return m_left_bottom_corner;
}

sf::Sprite Border::GetRightTopCorner(int posX, int posY)
{
	m_right_top_corner.setPosition(posX, posY);
	return m_right_top_corner;
}

sf::Sprite Border::GetRightBottomCorner(int posX, int posY)
{
	m_right_bottom_corner.setPosition(posX, posY);
	return m_right_bottom_corner;
}

sf::Sprite Border::GetVerticalLeftWall(int posX, int posY)
{
	m_vertical_left_wall.setPosition(posX, posY);
	return m_vertical_left_wall;
}

sf::Sprite Border::GetVerticalRightWall(int posX, int posY)
{
	m_vertical_right_wall.setPosition(posX, posY);
	return m_vertical_right_wall;
}

sf::Sprite Border::GetHorizontalTopWall(int posX, int posY)
{
	m_horizontal_top_wall.setPosition(posX, posY);
	return m_horizontal_top_wall;
}

sf::Sprite Border::GetHorizontalBottomWall(int posX, int posY)
{
	m_horizontal_bottom_wall.setPosition(posX, posY);
	return m_horizontal_bottom_wall;
}

void Border::CreateMap(RenderWindow& window)
{	
	for (int i = 0; i < WIDTH_MAP; i++)
	{
		for (int j = 0; j < HEIGHT_MAP; j++)
		{
			if (i == 0 && j == 0)
				window.draw(this->GetLeftTopCorner(0, 0));
			else if (i < WIDTH_MAP - 1 && j == 0)
				window.draw(this->GetHorizontalTopWall(HORIZONTAL_WALL_WIDTH * i, 0));
			else if (i == WIDTH_MAP - 1 && j == 0)
				window.draw(this->GetRightTopCorner(CORNER_WIDTH * i, 0));
			else if (j > 0 && i == 0)
				window.draw(this->GetVerticalLeftWall(0, VERTICAL_WALL_HEIGHT * j));
			else if (j > 0 && i == WIDTH_MAP - 1)
				window.draw(this->GetVerticalRightWall(HORIZONTAL_WALL_WIDTH * i, VERTICAL_WALL_HEIGHT * j));
		}
	}
}

void Border::CreateMenu(RenderWindow& window)
{	
	for (int i = WIDTH_MAP; i < WIDTH_MENU; i++)
	{
		for (int j = 0; j < HEIGHT_MENU; j++)
		{
			if (i == WIDTH_MAP && j == 0)
				window.draw(this->GetLeftTopCorner((CORNER_WIDTH * i), 0));
			else if (i < WIDTH_MENU - 1 && j == 0)
				window.draw(this->GetHorizontalTopWall(HORIZONTAL_WALL_WIDTH * i, 0));
			else if (i == WIDTH_MENU - 1 && j == 0)
				window.draw(this->GetRightTopCorner(CORNER_WIDTH * i, 0));
			else if (j > 0 && i == WIDTH_MAP && j < HEIGHT_MENU - 1)
				window.draw(this->GetVerticalLeftWall(HORIZONTAL_WALL_WIDTH * i, VERTICAL_WALL_HEIGHT * j));
			else if (j > 0 && i == WIDTH_MENU - 1 && j < HEIGHT_MENU - 1)
				window.draw(this->GetVerticalRightWall(HORIZONTAL_WALL_WIDTH * i, VERTICAL_WALL_HEIGHT * j));
			else if (j == HEIGHT_MENU - 1 && i == WIDTH_MAP)
				window.draw(this->GetLeftBottomCorner(HORIZONTAL_WALL_WIDTH * i, VERTICAL_WALL_HEIGHT * j));
			else if (j == HEIGHT_MENU - 1 && i == WIDTH_MENU - 1)
				window.draw(this->GetRightBottomCorner(HORIZONTAL_WALL_WIDTH * i, VERTICAL_WALL_HEIGHT * j));
			else if (j == HEIGHT_MENU - 1 && i > WIDTH_MAP && i < WIDTH_MENU - 1)
				window.draw(this->GetHorizontalBottomWall(HORIZONTAL_WALL_WIDTH * i, VERTICAL_WALL_HEIGHT * j));
		}
	}
}





