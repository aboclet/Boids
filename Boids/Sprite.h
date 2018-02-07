#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>

#include <SDL.h>

/// This class stores a texture image which you can draw where you want!
class Sprite
{
public:

	Sprite();
	~Sprite();

	bool LoadFromBMP(std::string filename, bool transp, SDL_Renderer *renderer);

	void Draw(int positionX, int positionY, float angle, SDL_Renderer *renderer);

protected:

	SDL_Texture *_texture;
	SDL_RendererFlip flip;
};



#endif
