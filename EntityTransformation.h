#pragma once

#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library

using namespace DirectX; //Use default DX11 Naming conventions
struct EntityTransformation
{
	XMFLOAT3 Translation;
	XMFLOAT3 Scale;
	XMFLOAT3 Rotation;
};