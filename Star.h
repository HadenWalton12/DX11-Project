#pragma once
#include "ObjectComponent.h"
#include "PixelShader.h"
#include "DX.h"
#include "VertexShader.h"
#include "Transformation.h"
#include "Surface.h"
#include "TimeStructure.h"
#include "Object.h"
class Star
{
public:
	Star::Star(RenderCommands* render_command, TextureComponent* _Tex)
	{

		_pRenderCommand = render_command;
		_Star = Object(_pRenderCommand, L"Crate_COLOR.dds", _Tex , "Star.Obj");
		
		XMFLOAT4 Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		XMFLOAT4 Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		XMFLOAT4 Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		FLOAT SpecularPower = 10.0f;

		_Star.SetSurface(Ambient , Diffuse , Specular , SpecularPower);
		_Star.SetVertexShader(L"DX11 Framework.fx");
		_Star.SetPixelShader(L"DX11 Framework.fx");
	}

	Star::~Star()
	{
		Cleanup();


	}
	void WorldTransformations() 
	{
		Timer t;
		XMFLOAT3 translation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		XMFLOAT3 rotation = XMFLOAT3(0.0f, 5.0f * t.gTime, 0.0f);
		
		_Star.SetTransformation(translation , scale , rotation , t);
	}
	
	
	
	Surface GetSurface()
	{
		return _Star._ObjectMaterial;
	}

	void Cleanup()
	{

		delete(_VS);
		delete(_PS);

		delete(_pRenderCommand);
	}


	Timer  t;
	
	Object _Star;
	Surface shinyMaterial;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader _VertexShader;
	PixelShader _PixelShader;
	RenderCommands* _pRenderCommand;
};