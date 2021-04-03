
#ifndef BORDER_H_
#define BORDER_H_

class Block;
class Border
{
public:
	Border();
	Border(const Border&) = delete;
	~Border() {}
		
	Border operator=(const Border&) const = delete;
	Border operator+(const Border&) const = delete;
		
	Sprite GetLeftTopCorner(int posX, int posY);
	Sprite GetLeftBottomCorner(int posX, int posY);
	Sprite GetRightTopCorner(int posX, int posY);
	Sprite GetRightBottomCorner(int posX, int posY);
	Sprite GetVerticalLeftWall(int posX, int posY);
	Sprite GetVerticalRightWall(int posX, int posY);
	Sprite GetHorizontalTopWall(int posX, int posY);
	Sprite GetHorizontalBottomWall(int posX, int posY);

	void CreateMap(RenderWindow& window);
	void CreateMenu(RenderWindow& window);

private:
	Image m_image;
	Texture m_texture;

	//tiles corners and walls
	Sprite m_vertical_left_wall;
	Sprite m_vertical_right_wall;
	Sprite m_horizontal_top_wall;
	Sprite m_horizontal_bottom_wall;
	Sprite m_left_top_corner;
	Sprite m_left_bottom_corner;
	Sprite m_right_top_corner;
	Sprite m_right_bottom_corner;
};

#endif