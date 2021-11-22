#pragma once
#include "ObjectComponent.h"

class Star : public GameObjects
{
public:
	Star::Star(GraphicComponent* gfx , ShaderComponent* _Shader , TextureComponent* _Tex) : GameObjects(gfx, "Star.obj") {}
	
	void Update(GraphicComponent* gfx) override 
	{
		Timer t;
        gfx->UpdateConstantBuffer();
        XMStoreFloat4x4(&gfx->_world, XMMatrixRotationY(t.time) * XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	}
};