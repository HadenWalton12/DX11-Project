#pragma once
#include "ObjectComponent.h"
#include "PixelShader.h"
#include "DX.h"
#include "VertexShader.h"
#include "ObjectTranformation.h"
#include "EntityTransformation.h"
#include "TimeStructure.h"
class Star : public GameObjects
{
public:
	Star::Star(RenderCommands* render_command, TextureComponent* _Tex, DX* dx) : GameObjects(render_command)
	{	
		_pDX11 = dx;
		_pRenderCommand = render_command;
		LoadMesh();
		_pStarTransform = new ObjectTranformation(&_StarWorld);
	}

	Star::~Star()
	{
		Cleanup();


	}
	void WorldTransformations() override
	{
		Timer t;
		_pStarTransform->SetTranslation(0.0f, 0.0f, 0.0f);
		_pStarTransform->SetScale(1.0f, 1.0f, 1.0f);
		t.Update();
		_pStarTransform->SetRotation(0.0f, 1.0f *t.gTime , 0.0f);
		_pStarTransform->CalculateWorldTransformation(_StarWorld);
		
		SetWorld(_pStarTransform->GetWorld());
	}
	MeshData LoadMesh() 	
	{
		_mesh = OBJLoader::Load("Star.obj", _pRenderCommand->GetDevice());
		return _mesh;
	}
	void BindShaders() override
	{
		_pVertexShader = new VertexShader(_pRenderCommand->GetDevice(), _VS, _pRenderCommand->GetDeviceContext(), L"DX11 Framework.fx");
		_pPixelShader = new PixelShader(_pRenderCommand->GetDevice(), _PS, L"DX11 Framework.fx");
		_VS = _pVertexShader->GetShader();
		_PS = _pPixelShader->GetShader();
		_pRenderCommand->BindVertexShader(_VS);
		_pRenderCommand->BindPixelShader(_PS);
		_pRenderCommand->BindSampler(_pDX11->_pSamplerLinear);

	}

	void Cleanup()
	{

		delete(_pStarTransform);
		delete(_VS);
		delete(_PS);
		delete(_pVertexShader);
		delete(_pPixelShader);
		delete(_pDX11);
		delete(_pRenderCommand);
	}

	Timer  t;
	

	XMFLOAT4X4 _StarWorld;
	ObjectTranformation* _pStarTransform;
	EntityTransformation transformation;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader* _pVertexShader;
	DX* _pDX11;
	PixelShader* _pPixelShader;
	RenderCommands* _pRenderCommand;
};