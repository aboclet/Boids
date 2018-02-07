#include <iostream>
//#include <time.h>
#include "Boid.h"

const float PI = 3.1415926535897932384626433832795f;

Boid::Boid(SDL_Renderer *render, int id, float x, float y, float angle)
{
	points.x = x;
	points.y = y;
	ID = id;
	angleRADS = angle * 180 / PI;
	sprite = new Sprite();
	filename = "boid.bmp";
	rend = render;
	sprite->LoadFromBMP(filename, true, rend);
	//velocity.x = 100.0f * cos(angleRADS);
	//velocity.y = 100.0f * sin(angleRADS);
}

Boid::~Boid()
{

}

void Boid::Update(float dt, Vec2 coh, Vec2 sep, Vec2 ali)
{
	if (points.x < 0.0f || points.x > 640.0f || points.y < 0.0f || points.y > 480.0f)
	{
		ChangePosition();
	}
	cohesion = coh;
	separation = sep;
	alignment = ali;

	velocity.x += coh.x * 0.1f + sep.x * 0.3f + ali.x * 0.1f;
	velocity.y += coh.y * 0.1f + sep.y * 0.3f + ali.y * 0.1f;
	Normalise(velocity);

	angleRADS = atan2(velocity.y, velocity.x);
	velocity.x = 100.0f * cos(angleRADS);
	velocity.y = 100.0f * sin(angleRADS);

	points.x += velocity.x * dt;
	points.y += velocity.y * dt;
}

void Boid::Draw()
{
	/*SDL_Rect fillRect = { points.x, points.y, 5.0f, 5.0f };
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 0);
	SDL_RenderFillRect(rend, &fillRect);*/
	sprite->Draw(points.x, points.y, angleRADS * (180/PI), rend);
}

Vec2 Boid::ReturnVelocity()
{
	return velocity;
}

int Boid::ReturnID()
{
	return ID;
}

void Boid::ChangePosition()
{
	
	if (points.y < 0.0f)
	{
		points.y = 480.0f;
	}

	if (points.y > 480.0f)
	{
		points.y = 0.0f;
	}

	if (points.x < 0.0f)
	{
		points.x = 640.0f;
	}

	if (points.x > 640.0f)
	{
		points.x = 0.0f;
	}
}

Vec2 Boid::ReturnPosition()
{
	return points;
}

float Boid::ReturnAngle()
{
	return angleRADS;
}
