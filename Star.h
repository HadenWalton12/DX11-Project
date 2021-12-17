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
	Star::Star(RenderCommands* render_command, TextureComponent* _Tex, XMFLOAT4X4 world, DX* dx) : GameObjects(render_command, "Star.obj")
	{

		_World = world;
		_pDX11 = dx;
		_pRenderCommand = render_command;


	
	}

	void CalculateTransformation()
	{
		Timer t;
		XMMATRIX scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
		XMMATRIX translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x, ObjectRotation.y * t.time, ObjectRotation.z);


		XMStoreFloat4x4(&world, scale * translation * rotation);
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
	XMFLOAT3 _StarTranslate = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 _StarScale = XMFLOAT3(0.02f, 0.02f, 0.02f);
	XMFLOAT3 _StarRotate = XMFLOAT3(0.0f, 1.0f * t.time, 0.0f);
	XMFLOAT4X4 _World;
	ObjectTranformation* _pStarTransform;
	EntityTransformation transformation;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader* _pVertexShader;
	DX* _pDX11;
	PixelShader* _pPixelShader;
	RenderCommands* _pRenderCommand;
};