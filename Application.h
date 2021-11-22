#pragma once
#include "SimpleVertexStructure.h"
#include "LightingValuesStructure.h"
#include "ConstantStructure.h"
#include "MeshStructure.h"
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
#include "ShaderComponent.h"
#include "TextureComponent.h"
#include "Star.h"
#include <vector>

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

	float rotationSpeed = 1.0f;

	float rotationValue = 0.0f;
	float previousRotation = 0.0f;

	Star* _star;
	GraphicComponent* _gfx;
	TextureComponent* _Tex;
	ShaderComponent* _Shader;
	std::vector<GameObjects*> _GameObjects;
	XMFLOAT4X4				_world;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;
/*
	// Interfaces/manages vertex shader  that controls vertex-shader stage (stage on pipeline)
	ID3D11VertexShader*     _pVertexShader;			   
	//Interfaces/manages the pixel shader that controls pixel-shader stage (Stage on PipeLine) 
	ID3D11PixelShader*      _pPixelShader;
	
	//Input Layout holds definition of how to feed vertex data laid out in memory (Buffers)into input-assembler stage
	ID3D11InputLayout*      _pVertexLayout;
	
	//ID3D11Buffer* - This is a buffer interface that allows to access a buffer resource, this being unstructured memory
	//These buffers will allow us to store vertex or index data
	ID3D11Buffer* _pCubeVertexBuffer;
	ID3D11Buffer* _pTriangleVertexBuffer;
	ID3D11Buffer* _pGridVertexBuffer;
	ID3D11Buffer*           _pCubeIndexBuffer; 
	ID3D11Buffer*			_pTriangleIndexBuffer;
	ID3D11Buffer* _pGridIndexBuffer;
	
	//We can then use this to create the relevant world,view,projection matrices that we need.
	//We store this data in 4x4 Matrix to transpose/ mathmatically apply matrix mathmatic too.
	XMFLOAT4X4				_world , _world2, _world3, _world4 , _world5, _world6, _world7 , objTestWorld;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;
	XMFLOAT4X4				 _grid;



	MeshData objStarMeshData;
	*/
private:

	//HRESULT CreateVertexBuffer();
	//HRESULT CreateIndexBuffer();



public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	HRESULT Update();
	void Draw();

};

