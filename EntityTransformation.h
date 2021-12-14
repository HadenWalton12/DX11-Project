#pragma once
#include "TransformationStructure.h"

class EntityTransformation
{
public:

	EntityTransformation(XMFLOAT4X4 world ,XMFLOAT3 Translation, XMFLOAT3 Rotation, XMFLOAT3 Scale)
	{

		XMMATRIX scale = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
		XMMATRIX translation = XMMatrixTranslation(Translation.x, Translation.y, Translation.z);
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z);


		XMStoreFloat4x4(&world, scale * translation * rotation);
	}


};