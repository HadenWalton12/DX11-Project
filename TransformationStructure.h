#pragma once
#pragma once
#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library


using namespace DirectX; //Use default DX11 Naming 

struct Translation
{
	XMFLOAT3 Translation;
};

struct Rotation
{
	XMFLOAT3 Rotation;
};

struct Scale
{
	XMFLOAT3 Scale;
};