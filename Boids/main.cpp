#include <SDL.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Boid.h"
#include "Sprite.h"
#include "Vec2.h"

Vec2 Cohesion(int id, std::vector <Boid> &boids);
Vec2 Separation(int id, std::vector <Boid> &boids);
Vec2 Alignment(int id, std::vector <Boid> &boids);

int main(int argc, char *argv[])
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}

	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 640;
	int winHeight = 480;
	SDL_Window *window = SDL_CreateWindow("Flocking",
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	unsigned int lastTime = SDL_GetTicks();
	float deltaTs = 0.0f;

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	bool cohesion = false;
	bool separation = false;
	bool alignment = false;

	int mousex = 0;
	int mousey = 0;

	std::vector<Boid>boids;
	srand(time(0));

	for (int i = 0; i < 50; i++)
	{
		boids.push_back(Boid(renderer, i, rand() % 640, rand() % 480, rand() % 360));
	}

	bool go = true;
	while (go)
	{

		SDL_Event incomingEvent;

		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{

				case SDL_QUIT:

					go = false;
					break;

				case SDL_MOUSEMOTION:
				{
					mousex = incomingEvent.motion.x;
					mousey = incomingEvent.motion.y;
				}
					break;

				case SDL_MOUSEBUTTONDOWN:
				{
					switch (incomingEvent.button.button)
					{
						case SDL_BUTTON_LEFT:
						{
							boids.push_back(Boid(renderer, boids.size() + 1, mousex, mousey, 80.0f));
							std::cout << "angle = " << boids[0].ReturnAngle();
						}
							break;
					}
					break;
				}
			}

		}

		unsigned int current = SDL_GetTicks();

		deltaTs = (float)(current - lastTime) / 1000.0f;

		lastTime = current;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		for (int i = 0; i < boids.size(); i++)
		{
			boids[i].Update(deltaTs, Cohesion(i, boids), Separation(i, boids), Alignment(i, boids));
			boids[i].Draw();
		}

		SDL_RenderPresent(renderer);

		if (deltaTs < (1.0f / 50.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

Vec2 Cohesion(int id, std::vector <Boid> &boids)
{
	Vec2 sum = { 0.0f, 0.0f };
	float desSep = 500.0f;
	int count = 0;
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		if (boids[i].ReturnID() != id)
		{
			if (distance(boids[i].ReturnPosition(), boids[id].ReturnPosition()) < desSep)
			{
				sum.x += boids[i].ReturnPosition().x;
				sum.y += boids[i].ReturnPosition().y;
				count++;
			}
		}
		
		
	}
	if (count == 0)
	{
		return sum;
	}
	sum.x /= count;
	sum.y /= count;
	sum = { sum.x - boids[id].ReturnPosition().x, sum.x - boids[id].ReturnPosition().y };
	Normalise(sum);
	return sum;

}

Vec2 Separation(int id, std::vector <Boid> &boids)
{

	float desSep = 50.0f;
	Vec2 diff = { 0.0f, 0.0f };
	int count = 0;
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		if (boids[i].ReturnID() != id)
		{
			if (distance(boids[i].ReturnPosition(), boids[id].ReturnPosition()) < desSep)
			{
				diff.x += boids[i].ReturnPosition().x - boids[id].ReturnPosition().x;
				diff.y += boids[i].ReturnPosition().y - boids[id].ReturnPosition().y;
				count++;
			}
		}
	}
	if (count == 0)
	{
		return diff;
	}

	diff.x /= count;
	diff.y /= count;
	diff.x *= -1;
	diff.y *= -1;
	Normalise(diff);
	return diff;
}

Vec2 Alignment(int id, std::vector <Boid> &boids)
{
	Vec2 sum = { 0.0f, 0.0f };
	int count = 0;
	float desSep = 25.0f;
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		if (boids[i].ReturnID() != id)
		{
			if (distance(boids[i].ReturnPosition(), boids[id].ReturnPosition()) < desSep)
			{
				sum.x += boids[i].ReturnVelocity().x;
				sum.y += boids[i].ReturnVelocity().y;
				count++;
			}
		}
	}
	if (count == 0)
	{
		return sum;
	}
	sum.x /= count;
	sum.y /= count;
	Normalise(sum);
	return sum;
}