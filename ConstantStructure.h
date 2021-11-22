#pragma once
#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;


//Constant Buffer - This allows you to supply shader constants data to pipeline , data we want to continously supply 
//We store these within since our matrices update in realtime  as game state changes , our view as we may move around the screen
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
