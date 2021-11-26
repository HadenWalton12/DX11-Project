#pragma once
#include "ObjectComponent.h"

class Star : public GameObjects
{
public:
	Star::Star(GraphicComponent* gfx , ShaderComponent* _Shader , TextureComponent* _Tex , XMFLOAT4X4 world) : GameObjects(gfx, "Star.obj") {}
	

};