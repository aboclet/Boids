#pragma once
#include <SDL.h>
#include <vector>
#include "Vec2.h"
#include "Sprite.h"

class Boid
{
private:
	Vec2 points;
	Vec2 cohesion;
	Vec2 separation;
	Vec2 alignment;
	Vec2 velocity;

	Sprite *sprite;

	std::string filename;

	int ID;

	float angleRADS;
	float speed;
	float headingAngle;

	SDL_Renderer *rend;

public:
	Boid(SDL_Renderer *render,int id, float x, float y, float angle);
	~Boid();
	void Update(float dt, Vec2 coh, Vec2 sep, Vec2 ali);
	void Draw();
	void ChangePosition();
	float ReturnAngle();

	Vec2 ReturnPosition();
	Vec2 ReturnVelocity();
	int ReturnID();
};