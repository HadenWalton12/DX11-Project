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
#include "Plane.h"
#include "Sphere.h"

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
	Plane* _plane;
	Sphere* _sphere;
	GraphicComponent* _gfx;
	TextureComponent* _Tex;
	ShaderComponent* _Shader;
	CameraComponent* _Camera;
	CameraComponent* _Camera2;
	std::vector<GameObjects*> _GameObjects;

public:

	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	HRESULT Update();
	void Draw();

};

