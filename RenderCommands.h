#pragma once
//Libraries used to create application  

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library
#include "ConstantStructure.h"
#include "LightingValuesStructure.h"
#include "DDSTextureLoader.h"
#include <vector>
#include "MeshStructure.h"
#include "OBJLoader.h"
#include "CameraComponent.h"


using namespace DirectX; //Use default DX11 Naming conventions

class RenderingCommand
{
public:
	RenderingCommand(ID3D11Device* device, ID3D11DeviceContext* device_context) : _pDevice(device), _pDeviceContext(device_context)
	{}

	

	ID3D11Device* _pDevice;
	ID3D11DeviceContext* _pDeviceContext;
	CameraComponent* _Camera;

};