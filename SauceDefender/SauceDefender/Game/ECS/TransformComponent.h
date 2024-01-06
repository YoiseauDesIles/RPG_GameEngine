#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:

	Vector2D position;

	TransformComponent(): position({0.0f, 0.0f})
	{ 
	}
	TransformComponent(float x, float y): position({x, y})
	{
	}

	void update() override
	{
		
	}


};