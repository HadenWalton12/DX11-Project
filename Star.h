#pragma once
#include "ObjectComponent.h"
#include "PixelShader.h"
#include "DX.h"
#include "VertexShader.h"
#include "Transformation.h"
#include "Surface.h"
#include "TimeStructure.h"
class Star : public GameObjects
{
public:
	Star::Star(RenderCommands* render_command, TextureComponent* _Tex, DX* dx) : GameObjects(render_command)
	{	
		_pDX11 = dx;
		_pRenderCommand = render_command;
		LoadMesh();

		shinyMaterial.ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		shinyMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		shinyMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		shinyMaterial.specularPower = 10.0f;

	}

	Star::~Star()
	{
		Cleanup();


	}
	void WorldTransformations() override
	{
		Timer t;
		XMFLOAT3 translation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		XMFLOAT3 rotation = XMFLOAT3(0.0f, 1.0f * t.gTime, 0.0f);
		Transformation _transformation = Transformation(translation , scale , rotation);


		t.Update();
	

		SetWorld(_transformation.GetWorld());
	}
	MeshData LoadMesh() 	
	{
		_mesh = OBJLoader::Load("Star.obj", _pRenderCommand->GetDevice());
		return _mesh;
	}
	void BindShaders() override
	{
		_VertexShader = VertexShader(L"DX11 Framework.fx" , _pRenderCommand->GetDevice() , _pRenderCommand->GetDeviceContext());
		_PixelShader = PixelShader(L"DX11 Framework.fx" , _pRenderCommand->GetDevice());
		_VS = _VertexShader.GetVertexShader();
		_PS = _PixelShader.GetPixelShader();
		_pRenderCommand->BindVertexShader(_VS);
		_pRenderCommand->BindPixelShader(_PS);
		_pRenderCommand->BindSampler(_pDX11->_pSamplerLinear);

	}


	
	Surface GetSurface() override
	{
		return shinyMaterial;
	}

	void Cleanup()
	{

		delete(_VS);
		delete(_PS);

		delete(_pDX11);
		delete(_pRenderCommand);
	}


	Timer  t;
	XMFLOAT4X4 _StarWorld;

	Surface shinyMaterial;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader _VertexShader;
	DX* _pDX11;
	PixelShader _PixelShader;
	RenderCommands* _pRenderCommand;
};