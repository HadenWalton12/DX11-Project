#pragma once//Libraries used to create application  

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library

#include "GraphicComponent.h"

using namespace DirectX; //Use default DX11 Naming conventions

class VertexBufferComponent
{
public:

	ID3D11Buffer* VertexBuffer;

	void SwitchVertexBuffer(ID3D11Buffer* VB , GraphicComponent* _gfx);
};

