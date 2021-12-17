#pragma once

#include "TimeStructure.h"
class ObjectTranformation
{
public:
	ObjectTranformation(XMFLOAT4X4* world)
	{
		XMStoreFloat4x4(world, XMMatrixIdentity());
	}

	
	void CalculateWorldTransformation(XMFLOAT4X4 world)
	{
		Timer t;
		XMMATRIX l_scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
		XMMATRIX l_translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
		XMMATRIX l_rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x, ObjectRotation.y , ObjectRotation.z);

		XMStoreFloat4x4(&world, l_scale * l_translation * l_rotation);
		_World = world;
	}

	XMFLOAT4X4 GetWorld()
	{
		return _World;
	}

	void SetRotation(float x, float y, float z)
	{
		ObjectRotation = XMFLOAT3(x, y, z);
	}

	void SetTranslation(float x, float y, float z)
	{
		ObjectTranslation = XMFLOAT3(x, y, z);
	}
	void SetScale(float x, float y, float z)
	{
		ObjectScale = XMFLOAT3(x, y, z);
	}

private:

	XMFLOAT3 ObjectTranslation;							
	XMFLOAT3 ObjectRotation;							
	XMFLOAT3 ObjectScale;

	XMFLOAT4X4 _World;
};

