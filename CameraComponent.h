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
	
	//Storing of camera positional values 
private:

	XMVECTOR eye;
	XMVECTOR at;
	XMVECTOR up;

	float _WindowWidth;
	float _WindowHeight;
	float _NearDepth;
	float _FarDepth;


public:

	//Constructor and destructor for the camera

	//Matrices passed to shader to apply lighting ect...

	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection; 
	CameraComponent(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth, float farDepth);
	~CameraComponent();

	void SetEye(XMFLOAT3 eye);
	void SetAt(XMFLOAT3 at);
	void SetUp(XMFLOAT3 up);

	XMFLOAT3 GetEye();
	XMFLOAT3 GetAt();
	XMFLOAT3 GetUp();

	XMFLOAT4X4 GetView();
	XMFLOAT4X4 GetProjection();

	//Use to move camera
	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;
	//Rotate the camera
	XMMATRIX camRotationMatrix;

	//Move left and right
	float moveLeftRight = 0.0f;

	//Move back and forward
	float moveBackForward = 0.0f;

	//Vertical Rotation
	float camYaw = 0.0f;
	//Horizontal rotation
	float camPitch = 0.0f;
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();


	void Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth);

	// update function to make the current view and projection 
// matrices
	void Update();


};

