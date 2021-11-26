#pragma once
#include "ObjectComponent.h"

class Plane : public GameObjects
{
public:
	Plane::Plane(GraphicComponent* gfx, ShaderComponent* _Shader, TextureComponent* _Tex, XMFLOAT4X4 world) : GameObjects(gfx, "Hercules.obj") {}

	void CalculateTransformation() 
	{
	
		Timer t;
		XMMATRIX scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
		XMMATRIX translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x * t.time, ObjectRotation.y , ObjectRotation.z);


		XMStoreFloat4x4(&world, scale * translation * rotation);
	}

};