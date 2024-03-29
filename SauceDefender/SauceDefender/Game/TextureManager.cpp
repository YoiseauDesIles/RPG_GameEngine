#include "TextureManager.h"
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const std::string& textureFile)
{
	SDL_Surface* tmpSurface = IMG_Load(textureFile.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);

	SDL_FreeSurface(tmpSurface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, NULL, NULL, flip);
}
