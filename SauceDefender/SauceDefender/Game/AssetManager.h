#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
//#include "ECS/Components.h"

class AssetManager
{
private:
	std::map<std::string, SDL_Texture*> textures;
	Manager* manager;

public:
	AssetManager(Manager* manager);
	~AssetManager();

	//game objets
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	//texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
};