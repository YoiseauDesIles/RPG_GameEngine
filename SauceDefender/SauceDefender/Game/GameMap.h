#pragma once
#include <string>


class GameMap
{
private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;

public:
	GameMap(std::string texID, int mapScale, int tileSize);
	~GameMap();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int posX, int posY);
	

};
