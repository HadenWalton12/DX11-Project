#pragma once
#include "ObjectComponent.h"

class Sphere : public GameObjects
{
public:
	Sphere::Sphere(GraphicComponent* gfx, ShaderComponent* _Shader, TextureComponent* _Tex, XMFLOAT4X4 world) : GameObjects(gfx) {}


};