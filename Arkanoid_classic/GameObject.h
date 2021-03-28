

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Config.h"

using std::string;
using namespace sf;

//---------------------------------------------Game Object--------------------------------------------------
class GameObject : public Sprite
{

protected:
	
	Image& _image;
	Texture _texture;

public:
	//конструторы
	GameObject(Image &img);
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}


	//Методы
	FloatRect GetRect();


	Image& GetImage() { return _image; }	
	Texture GetTexture() { return _texture; }
	void SetTexture() { _texture.loadFromImage(_image); }
};


#endif 


