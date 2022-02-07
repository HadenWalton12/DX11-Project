#pragma once
#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;



	struct Transformation
	{

		XMFLOAT4X4 World;
		XMFLOAT3 Translation;
		XMFLOAT3 Scale;
		XMFLOAT3 Rotation;


		Transformation(XMFLOAT3 translation , XMFLOAT3 scale , XMFLOAT3 rotation)
		{
			XMMATRIX _Translation = XMMatrixTranslation(translation.x, translation.y, translation.z);
			XMMATRIX _Scale = XMMatrixScaling(scale.x, scale.y, scale.z);
			XMMATRIX _Rotation = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

			Translation = translation;
			Scale = scale;
			Rotation = rotation;

			XMStoreFloat4x4(&World, _Translation * _Scale * _Rotation);
		}

		XMFLOAT4X4 GetWorld()
		{
			return World;
		}

		XMFLOAT3 GetRotation()
		{
			return Rotation;

		}

		XMFLOAT3 GetScale()
		{
			return Scale;

		}

		XMFLOAT3 GetTranslate()
		{
			return Translation;

		}

		void SetRotation(float x, float y, float z)
		{
			Rotation = XMFLOAT3(x, y, z);
		}

		void SetTranslation(float x, float y, float z)
		{
			Translation = XMFLOAT3(x, y, z);
		}

		void SetScale(float x, float y, float z)
		{
			Scale = XMFLOAT3(x, y, z);
		}
	};
