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
	XMFLOAT3 Camera_Direction;
	XMFLOAT3 Camera_Up;

	float _WindowWidth;
	float _WindowHeight;
	float _NearDepth;
	float _FarDepth;


public:


	//Matrices passed to shader to apply lighting ect...

	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection; 
	CameraComponent(XMFLOAT3 camera_position, XMFLOAT3 camera_direction, XMFLOAT3 camera_up, float windowWidth, float windowHeight, float nearDepth, float farDepth);
	~CameraComponent();

	void SetPosition(XMFLOAT3 position);
	void SetDirection(XMFLOAT3 direction);
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetDirection();
	XMFLOAT4X4 GetView();
	XMFLOAT4X4 GetProjection();

	void SetView(XMFLOAT3 camera_position, XMFLOAT3 camera_target, XMFLOAT3 camera_up);
	void SetProjection();

	// update function to make the current view and projection 
// matrices
	void Update();

	XMVECTOR CameraPosition;
	XMVECTOR CameraTarget;
	XMVECTOR CameraUp;
	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR CameraForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR CameraRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMMATRIX CameraRotationMatrix;
	

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;

};

