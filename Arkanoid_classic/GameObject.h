

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Config.h"

using std::string;
using namespace sf;

//---------------------------------------------Game Object--------------------------------------------------
class GameObject : public Sprite
{

protected:
	
	Image _image;
	Texture _texture;

public:
	//�����������
	GameObject();
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}


	//������
	FloatRect GetRect();

	Image GetImage() { return _image; };
	void SetImage(string path) { _image.loadFromFile(path); }

	Texture GetTexture() { return _texture; }
	void SetTexture() { _texture.loadFromImage(_image); }
};


#endif 


