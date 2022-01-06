#pragma once
#include "ObjectComponent.h"
#include "PixelShader.h"
#define TO_RADIANS 3.14/180 //Converts degrees to radians upon multiplication

#include "DX.h"
#include "VertexShader.h"
#include "ObjectTranformation.h"
#include "InputComponent.h"
#include "EntityTransformation.h"
#include "TimeStructure.h"
class Cylinder : public GameObjects
{
public:
	Cylinder::Cylinder(RenderCommands* render_command, TextureComponent* _Tex, DX* dx, InputComponent* input) : GameObjects(render_command)
	{
		_pDX11 = dx;
		
		_pRenderCommand = render_command;
		CameraPosition = XMFLOAT3(0.0f, 5.0f, -5.0f);
		LoadMesh();
		_pCylinderTransform = new ObjectTranformation(&_CylinderWorld);
		_pCylinderTransform->SetTranslation(0.0f, 5.0f, 0.0f);
		_pCylinderTransform->SetScale(1.0f, 1.0f, 1.0f);
		_pCylinderTransform->SetRotation(0.0f, 0.0f, 0.0f);
	}

	Cylinder::~Cylinder()
	{
		Cleanup();
	}
	MeshData LoadMesh()
	{
		_mesh = OBJLoader::Load("cylinder.obj", _pRenderCommand->GetDevice());
		return _mesh;
	}

	
	void WorldTransformations() override
	{
		

		XMFLOAT3 ObjectTranslate = _pCylinderTransform->GetTranslate();

		_pCylinderTransform->SetTranslation(ObjectTranslate.x, ObjectTranslate.y, ObjectTranslate.z);
		_pCylinderTransform->CalculateWorldTransformation(_CylinderWorld);
		SetPosition(CameraPosition);
		SetWorld(_pCylinderTransform->GetWorld());
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
	XMFLOAT3 GetPosition()
	{
		return CameraPosition;
	}
	void SetPosition(XMFLOAT3 pos)
	{

		CameraPosition = pos;
	}

	void Cleanup()
	{
		delete(_pCylinderTransform);
		delete(_VS);
		delete(_PS);
		delete(_pVertexShader);
		delete(_pPixelShader);
		delete(_pDX11);
		delete(_pRenderCommand);
	}

	Timer  t;
	XMFLOAT4X4 _CylinderWorld;
	XMFLOAT3 CameraPosition;
	ObjectTranformation* _pCylinderTransform;
	EntityTransformation transformation;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader* _pVertexShader;
	DX* _pDX11;
	PixelShader* _pPixelShader;
	RenderCommands* _pRenderCommand;
};