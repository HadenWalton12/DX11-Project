#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 DiffuseLight;

	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 AmbientLight;

	XMFLOAT4 SpecularMtrl;
	XMFLOAT4 SpecularLight;
	float SpecularPower;

	XMFLOAT3 LightVecW;
	XMFLOAT4 EyePosW;

};