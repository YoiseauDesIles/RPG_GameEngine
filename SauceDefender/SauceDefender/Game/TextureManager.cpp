#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* textureFile, SDL_Renderer* ren)
{
	SDL_Surface* tmpSurface = IMG_Load(textureFile);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, tmpSurface);

	SDL_FreeSurface(tmpSurface);

	return texture;
}
