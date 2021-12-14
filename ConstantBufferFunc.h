#pragma once
///////////////////////////////////////////////////////////////////////////
/////////////////////////////// INDEX BUFFER //////////////////////////////
////CREATE NEW INSTANCE OF IB WHEN NEEDED TO BIND NEW DATA TO PIPELINE ////
///////////////////////////////////////////////////////////////////////////

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library


using namespace DirectX; //Use default DX11 Naming 

class ConstantBuffer
{
public:
	ConstantBuffer(ID3D11Device* device, ID3D11Buffer* CB) : _pDevice(device)
	{
		// Create the constant buffer
		D3D11_BUFFER_DESC constantbufferdescription;
		ZeroMemory(&constantbufferdescription, sizeof(constantbufferdescription));
		//Describe Constant Buffer
		constantbufferdescription.Usage = D3D11_USAGE_DEFAULT;
		constantbufferdescription.ByteWidth = sizeof(ConstantBuffer);
		constantbufferdescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantbufferdescription.CPUAccessFlags = 0;

		//Create Buffer - Using Description above , 3rd parameters assigns value to Constantbuffer buffer pointer.
		_pDevice->CreateBuffer(&constantbufferdescription, nullptr, CB);
	}


	ID3D11Device* _pDevice;
};