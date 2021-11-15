#pragma once
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
#include "ConstantBuffer.h"
#include "MeshStructure.h"

#include "DDSTextureLoader.h"
//Allows us to easily call reference upon our DX naming conventions
using namespace DirectX;

//XMFLOAT3 - Describes 3DVector , Consisting of Three Points (x,y ,z)
//XMFLOAT4 - Describes 4DVector , Consisting of Four Points (x)
//XMFLOAT4X4  - Structure that creates 4*4 Floating Point Matrix - Can be used to store XMMATRIX DATA
//and relevant matrix data within DX11



class Application
{
private:


	ID3D11Buffer* _pCubeVertexBuffer;
	ID3D11Buffer* _pTriangleVertexBuffer;
	ID3D11Buffer* _pGridVertexBuffer;
	ID3D11Buffer* _pCubeIndexBuffer;
	ID3D11Buffer* _pTriangleIndexBuffer;
	ID3D11Buffer* _pGridIndexBuffer;
	XMFLOAT4X4				_world, _world2, _world3, _world4, _world5, _world6, _world7, objTestWorld;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;
	XMFLOAT4X4				 _grid;

	MeshData objStarMeshData;

private:
	/*HRESULT - WINDOWS DATATYPE THAT IS USED TO DESCRIBE ERROR OR WARNING - Making this our function type allows us to return error/warning messages
	previously not possible without such type
	Intialises our Windows Application*/

	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT CreateDevice();

	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();

	void Cleanup();

	UINT _WindowHeight;
	UINT _WindowWidth;

public:
	Application();
	~Application();

	HRESULT Update();
	void Draw();

};

