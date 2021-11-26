#pragma once
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library
using namespace DirectX;
class Camera

{

private:

	// Private attributes to store the camera position and view

	XMFLOAT3 _eye;
	XMFLOAT3 _at;
	XMFLOAT3 _up;

	float  _windowWidth;
	float _windowHeight;

	float _nearDepth;
	float _farDepth;

	// attributes to hold the view and projection matrices which
	// will be passed to the shader

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;

public:


	Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth, float farDept);
	~Camera();

	void Update();
	void Reshape(FLOAT windowWidth, float windowHeight, float nearDepth, FLOAT farDepth);


	void GetProjection();
	void GetView();
	void GetViewProjection();





}



