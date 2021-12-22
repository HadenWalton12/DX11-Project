#pragma once
//Libraries used to create application  
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library


using namespace DirectX; //Use default DX11 Naming conventions


struct LigthtingValues
{
	XMFLOAT3 light_direction;
	XMFLOAT4 diffuse_material;
	XMFLOAT4 diffuse_light;
	XMFLOAT4 specular_material;
	XMFLOAT4 specular_light;
	XMFLOAT4 ambient_material;
	XMFLOAT4 ambient_light;
	float specular_power;
	XMFLOAT4 EyePosW;

	LigthtingValues()
	{
		light_direction = XMFLOAT3(2.5f, 0.0f, -4.0f);
		diffuse_material = XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f);
		diffuse_light = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.5f);
		ambient_light = XMFLOAT4(0.1f, 0.1f, 0.0f, 1.0f);
		ambient_material = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		specular_material = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		specular_light = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		specular_power = 1.0f;
		EyePosW = XMFLOAT4(0.0f, 0.0f, -5.0f, 0.0f);



	}
};
