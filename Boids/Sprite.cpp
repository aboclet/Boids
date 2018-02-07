#include <iostream>

#include "Sprite.h"

Sprite::Sprite()
{
	_texture = NULL;
	flip = SDL_FLIP_HORIZONTAL;
}

Sprite::~Sprite()
{
	if (_texture)
	{
		SDL_DestroyTexture(_texture);
	}
}

bool Sprite::LoadFromBMP(std::string filename, bool transp, SDL_Renderer *renderer)
{
	if (filename.empty())
	{
		std::cerr << "ERROR: Sprite::LoadFromBMP - empty filename given" << std::endl;
		return false;
	}

	SDL_Surface *image = SDL_LoadBMP(filename.c_str());

	SDL_SetColorKey(image, transp, SDL_MapRGB(image->format, 255, 0, 255));

	_texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);

	return true;
}

void Sprite::Draw(int positionX, int positionY, float angle, SDL_Renderer *renderer)
{
	SDL_Rect destRect;

	destRect.x = positionX;
	destRect.y = positionY;

	SDL_QueryTexture(_texture, NULL, NULL, &destRect.w, &destRect.h);

	SDL_RenderCopyEx(renderer, _texture, NULL, &destRect, angle, NULL, flip);

}
