#include "GameMap.h"
#include "Game.h"
#include <fstream>

GameMap::GameMap()
{

}

GameMap::~GameMap()
{
}

void GameMap::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			//TODO verifier pourquoi on met 2 fois get ici
			mapFile.get(tile);
			srcY = atoi(&tile) * 32;
			mapFile.get(tile);
			srcX = atoi(&tile) * 32;
			Game::AddTile(srcX, srcY, x * 64, y * 64);
			mapFile.ignore();
		}
	}

	mapFile.close();
}




