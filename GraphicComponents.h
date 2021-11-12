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


#include "DDSTextureLoader.h"
//Allows us to easily call reference upon our DX naming conventions
using namespace DirectX;


class GraphicComponents
{
private:
//Used to initialize our window 
	HINSTANCE               _hInst;
	HWND                    _hWnd;


private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);




	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();

	void Cleanup();


public:
	GraphicComponents();
	~GraphicComponents();


};

