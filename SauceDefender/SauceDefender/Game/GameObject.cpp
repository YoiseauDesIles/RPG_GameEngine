#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y) :
	m_xPos(x), m_yPos(y) 
{
	m_renderer = renderer;
	m_objTexture = TextureManager::LoadTexture(textureSheet, renderer);
}

GameObject::~GameObject()
{
}

void GameObject::update()
{

	m_xPos++;
	m_yPos++;

	m_srcRect.h = 32;
	m_srcRect.w = 32;
	m_srcRect.x = 0;
	m_srcRect.y = 0;	
	
	m_dstRect.x = m_xPos;
	m_dstRect.y = m_yPos;
	m_dstRect.w = m_srcRect.w * 2;
	m_dstRect.h = m_srcRect.h * 2;

}

void GameObject::render()
{
	SDL_RenderCopy(m_renderer, m_objTexture, &m_srcRect, &m_dstRect);
}
