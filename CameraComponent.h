#pragma once
#include "resource.h"
#include "LightingValuesStructure.h"
//Libraries used to create application  

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library

using namespace DirectX;

class CameraComponent
{
	
	//Storing of cam era positional values 
private:

	XMFLOAT3 Camera_Position;
	XMFLOAT3 Camera_Target;
	XMFLOAT3 Camera_Up;

	float Camera_Yaw;
	float Camera_Pitch;

	float _WindowWidth;
	float _WindowHeight;
	float _NearDepth;
	float _FarDepth;


public:
	

	
	XMMATRIX Camera_Rotation;

	float MoveRight;
	float MoveLeft;
	float MoveForward;
	float MoveBackwards;
	
	//Matrices passed to shader to apply lighting ect...

	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection; 
	CameraComponent(XMFLOAT3 camera_position, XMFLOAT3 camera_target, XMFLOAT3 camera_up, float windowWidth, float windowHeight, float nearDepth, float farDepth);
	~CameraComponent();

	void SetEye(XMFLOAT3 eye);
	void SetAt(XMFLOAT3 at);
	void SetUp(XMFLOAT3 up);

	XMFLOAT3 GetEye();
	XMFLOAT3 GetAt();
	XMFLOAT3 GetUp();

	XMFLOAT4X4 GetView();
	XMFLOAT4X4 GetProjection();

	void SetView(XMFLOAT3 camera_position, XMFLOAT3 camera_target, XMFLOAT3 camera_up);
	void SetProjection();

	void CameraMovement(float d);
	void Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth);

	// update function to make the current view and projection 
// matrices
	void Update();


};

