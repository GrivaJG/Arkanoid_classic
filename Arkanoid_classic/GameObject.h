

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Config.h"
//---------------------------------------------Game Object--------------------------------------------------
class GameObject : public Sprite
{
public:
	GameObject(Image& img);
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}

	FloatRect GetRect();
	Image& GetImage() { return m_image; }
	Texture GetTexture() { return m_texture; }
	void SetTexture() { m_texture.loadFromImage(m_image); }

protected:	
	Image& m_image;
	Texture m_texture;
};
#endif 


