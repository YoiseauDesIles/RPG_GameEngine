#pragma once
#include <string>


class GameMap
{
private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;

public:
	GameMap(const char* mapFilePath, int mapScale, int tileSize);
	~GameMap();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int posX, int posY);
	

};
