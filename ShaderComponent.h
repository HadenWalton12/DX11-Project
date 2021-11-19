#pragma once

#include "Structure.h"
#include "OBJLoader.h"
//Libraries used to create application 
//Makes it possible to create our window
#include <windows.h>
//Access to core DX functions 
#include <d3d11_1.h>
//Allows us to compile DX11 Code
#include <d3dcompiler.h>
//Math Library
#include <directxmath.h>
#include <directxcolors.h>
//Libraries used to create application 
//Makes it possible to create our window
#include <windows.h>
//Access to core DX functions 
#include <d3d11_1.h>
//Allows us to compile DX11 Code
#include <d3dcompiler.h>
//Math Library
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"

#include "GraphicComponent.h"


using namespace DirectX;




class ShaderComponent
{
public:

	ShaderComponent(GraphicComponent* gfx);
	~ShaderComponent();


	HRESULT CreateShaderandLayout();
	void ComposeShader();

private:
	GraphicComponent* _gfx;
	ID3D11Device* _device;
	ID3D11InputLayout* _pVertexLayout;

	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;



private:
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);



};

