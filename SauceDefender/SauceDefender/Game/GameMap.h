#pragma once

#include "Game.h"
#include <array>

class GameMap
{
public:
	GameMap();
	~GameMap();

	void LoadMap(int map[20][25]);
	void DrawMap();

private:
	SDL_Rect m_src, m_dst;

	SDL_Texture* m_pDirt;
	SDL_Texture* m_pGrass;
	SDL_Texture* m_pWater;

	int m_map[20][25];
};
