#pragma once
#include "ObjectComponent.h"
#include "PixelShader.h"

#include "DX.h"
#include "VertexShader.h"
#include "ObjectTranformation.h"
#include "InputComponent.h"
#include "EntityTransformation.h"
#include "TimeStructure.h"
class Plane : public GameObjects
{
public:
	Plane::Plane(RenderCommands* render_command, TextureComponent* _Tex, DX* dx ) : GameObjects(render_command) 
	{
		_pDX11 = dx;
		_pRenderCommand = render_command;
		LoadMesh();
		_pPlaneTransform = new ObjectTranformation(&_PlaneWorld);

	}
	MeshData LoadMesh() 
	{
		_mesh = OBJLoader::Load("Hercules.obj", _pRenderCommand->GetDevice());
		return _mesh;
	}
	void WorldTransformations() override
	{

		Timer t;
		t.Update();
		_pPlaneTransform->SetTranslation(0.0f, 2.0f, 0.0f);
		_pPlaneTransform->SetScale(0.10f, 0.10f, 0.10f);
		
		_pPlaneTransform->SetRotation(0.0f,0.0f, 0.0f);
		_pPlaneTransform->CalculateWorldTransformation(_PlaneWorld);

		SetWorld(_pPlaneTransform->GetWorld());
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



	Timer  t;
	XMFLOAT4X4 _PlaneWorld;
	ObjectTranformation* _pPlaneTransform;
	InputComponent* _PlaneInput;
	EntityTransformation transformation;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader* _pVertexShader;
	DX* _pDX11;
	PixelShader* _pPixelShader;
	RenderCommands* _pRenderCommand;
};