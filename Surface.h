#pragma once
#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;


struct Surface
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;

	float specularPower;




};