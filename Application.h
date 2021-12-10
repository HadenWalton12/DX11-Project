#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>

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

#include "ShaderComponent.h"
#include "TextureComponent.h"

#include "SkyBox.h"
#include "Star.h"
#include "Plane.h"
#include "Sphere.h"
#include "TerrainPlane.h"
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


	TerrainPlane* _Terrain;
	Star* _star;
	Plane* _plane;
	SkyBox* _skybox;
	//Sphere* _sphere;
	GraphicComponent* _gfx;
	TextureComponent* _Tex;
	ShaderComponent* _Shader;
	CameraComponent* _Camera;

	std::vector<GameObjects*> _GameObjects;

public:

	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	bool InitDirectInput(HINSTANCE hInstance);
	void DetectInput();

	IDirectInputDevice8* DIKeyBoard;
	IDirectInputDevice8* DIMouse;

	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

	float rotx = 0;
	float rotz = 0;
	float scaleX = 1.0f;
	float scaleY = 1.0f;

	XMMATRIX RotationX;
	XMMATRIX RotationZ;
	HRESULT Update();
	void Draw();

};

