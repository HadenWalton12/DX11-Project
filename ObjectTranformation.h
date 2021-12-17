#pragma once

#include "TimeStructure.h"
class ObjectTranformation
{
public:
	ObjectTranformation(XMFLOAT4X4 world , XMFLOAT3 translation , XMFLOAT3 scale , XMFLOAT3 rotation) : _World(world) , ObjectTranslation(translation) , ObjectRotation(rotation) , ObjectScale(scale)
	{
		UpdateTransformation();
	}
	void UpdateTransformation( )
	{
		
		XMMATRIX l_scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
		XMMATRIX l_translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
		XMMATRIX l_rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x, ObjectRotation.y , ObjectRotation.z);


		XMStoreFloat4x4(&_World, l_scale * l_translation * l_rotation);

	}



private:

	XMFLOAT3 ObjectTranslation;							
	XMFLOAT3 ObjectRotation;							
	XMFLOAT3 ObjectScale;
	XMFLOAT4X4 _World;
};

