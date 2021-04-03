
#include "GameObject.h"

GameObject::GameObject(Image& img) : m_image(img)
{   
    m_texture.loadFromImage(m_image);  
}

FloatRect GameObject::GetRect()
{
    return FloatRect(this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height);
}