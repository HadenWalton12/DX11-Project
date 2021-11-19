#pragma once
#include "ObjectComponent.h"

class Star : public GameObjects
{
public:
	

	Star::Star(GraphicComponent* gfx) : GameObjects(gfx, "Star.obj") {}
};