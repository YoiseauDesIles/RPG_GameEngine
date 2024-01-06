#include "GameMap.h"
#include "TextureManager.h"


//TMP map
int level1[20][25] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
};


GameMap::GameMap()
{
	m_pDirt = TextureManager::LoadTexture("Assets/dirt.png");
	m_pGrass = TextureManager::LoadTexture("Assets/grass.png");
	m_pWater= TextureManager::LoadTexture("Assets/water.png");

	LoadMap(level1);

	m_src.x = m_src.y = 0;
	m_dst.x = m_dst.y = 0;
	m_src.w = m_dst.w = 32;
	m_src.h = m_dst.h = 32;

}

GameMap::~GameMap()
{
	SDL_DestroyTexture(m_pGrass);
	SDL_DestroyTexture(m_pDirt);
	SDL_DestroyTexture(m_pWater);
}

void GameMap::LoadMap(int map[20][25])
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			m_map[row][column] = map[row][column];
		}
	}

}

void GameMap::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = m_map[row][column];
			m_dst.x = column * 32;
			m_dst.y = row * 32;

			switch (type) {
			case 0:
				TextureManager::Draw(m_pWater, m_src, m_dst);
				break;
			case 1:
				TextureManager::Draw(m_pGrass, m_src, m_dst);
				break;
			case 2:
				TextureManager::Draw(m_pDirt, m_src, m_dst);
				break;
			default:
				break;
			}
		}
	}
}

