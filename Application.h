#pragma once
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

#include "DX.h"
#include "RenderCommands.h"

#include "TextureComponent.h"

#include "Star.h"
#include "Terrain.h"
#include "Plane.h"
#include "Sphere.h"

#include "InputComponent.h"


#include <vector>

#include "DDSTextureLoader.h"
#include "PixelShader.h"
#include "VertexShader.h"

//
#include "PlaneCamera.h"
#include "StaticDefaultCamera.h"
#include "StaticTopDownCamera.h"
#include "DynamicMovementCamera.h"


//Allows us to easily call reference upon our DX naming conventions
using namespace DirectX;

//XMFLOAT3 - Describes 3DVector , Consisting of Three Points (x,y ,z)
//XMFLOAT4 - Describes 4DVector , Consisting of Four Points (x)
//XMFLOAT4X4  - Structure that creates 4*4 Floating Point Matrix - Can be used to store XMMATRIX DATA
//and relevant matrix data within DX11



class Application
{
private:

	DX* _pDX11;
	RenderCommands* _pRenderCommands;
	Terrain* _Terrain;
	Star* _star;
	Plane* _plane;
	Sphere* _sphere;
	
	TextureComponent* _Tex;
	
	PixelShader* _pPixelShader;
	VertexShader* _pVertexShader;
	
	ID3D11PixelShader* _PS;
	ID3D11VertexShader* _VS;
	
	InputComponent* _Input;

	DynamicMovementCamera* _DynamicMovementCamera;	
	PlaneCamera* _PlaneCamera;
	StaticTopDownCamera* _StaticTopDownCamera;
	StaticDefaultCamera* _StaticDefaultCamera;


	std::vector<GameObjects*> _GameObjects;
	std::vector<Camera*> _CameraObjects;

public:

	HINSTANCE               _hInst;								//Used to specify instance which the class is registred					
	HWND                    _hWnd;								//Used to handle a window , part of Win32 API , crates window using window instance above.

	UINT _WindowHeight;											//Define window height
	UINT _WindowWidth;											//Define window width


	Application() {};
	~Application() {};

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	

	

	HRESULT Update();
	void Draw();
	






	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow);

};

