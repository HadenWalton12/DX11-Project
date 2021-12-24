#pragma once
//Libraries used to create application  
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library



using namespace DirectX; //Use default DX11 Naming conventions

struct Timer
{

	float gTime;


	Timer()
	{
		// Update our time
		gTime = 5.0f;
			static DWORD dwTimeStart = 0;
			DWORD dwTimeCur = GetTickCount();


			gTime = (dwTimeCur - dwTimeStart) / 1000.0f;

	}
	void Update()
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();


		gTime = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

};