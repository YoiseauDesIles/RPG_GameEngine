#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent()
		: position(position.Zero()), velocity(velocity.Zero()), height(32), width(32), scale(1)
	{ 
	}

	TransformComponent(int sc)
		: position({0, 0}), velocity(velocity.Zero()), height(32), width(32), scale(sc)
	{
	}
	TransformComponent(float x, float y)
		: position({x, y}), velocity(velocity.Zero()), height(32), width(32), scale(1)
	{
	}

	TransformComponent(float x, float y, int h, int w, int sc) 
		: position({ x, y }), velocity(velocity.Zero()), height(h), width(w), scale(sc)
	{
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}


};