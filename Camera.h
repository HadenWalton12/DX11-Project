#pragma once
////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// CAMERA CLASS ///////////////////////////////////////////
//// AUTHORATIVE PARENT CLASS FOR ALL CAMERAS , VIRTUAL FUNCTIONS FOR THIS REASON   ////
////////////////////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include "LightingValuesStructure.h"
#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions

#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code
#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library

using namespace DirectX;

class Camera
{
public:

	Camera()
	{
		_NearDepth = 0.01f;
		_FarDepth = 100.0f;
		_WindowHeight = 640;
		_WindowWidth  = 480;
	}
	
	virtual void InitialiseView()
	{
		
	}

	// Initialize the projection matrix
	virtual void InitialiseProjection()
	{
	}

	virtual void UpdateCamera()
	{
	}

	//Getters
	virtual XMFLOAT4X4 GetView()
	{return _View;} 

	virtual XMFLOAT4X4 GetProjection()
	{return _Projection;}
protected:
	
	FLOAT _WindowWidth;
	FLOAT _WindowHeight;
	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection;
	FLOAT _NearDepth;
	FLOAT _FarDepth;
};