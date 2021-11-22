#pragma once
#include "ObjectComponent.h"

class Star : public GameObjects
{
public:
	Star::Star(GraphicComponent* gfx , ShaderComponent* _Shader , TextureComponent* _Tex) : GameObjects(gfx, "Star.obj") {}
	
};