#pragma once





class Border
{
private:
	Image image;
	Texture texture; 	//����� ������ (���� � �����)
	Sprite _verticalLeftWall;
	Sprite _verticalRightWall;
	Sprite _horizontalTopWall;
	Sprite _horizontalBottomWall;
	Sprite _leftTopCorner;
	Sprite _leftBottomCorner;
	Sprite _rightTopCorner;
	Sprite _rightBottomCorner;

	
	


public:
	//�����������
	Border();
	Border(const Border&) = delete;

	~Border() {}

	//���������������� ���������
	Border operator=(const Border&) const = delete;
	Border operator+(const Border& gmbj) const = delete;

	//������ ��������� �������� ������ �����
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


};

