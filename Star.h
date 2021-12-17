#pragma once
#include "ObjectComponent.h"
#include "PixelShader.h"
#include "VertexShader.h"
class Star : public GameObjects
{
public:
	Star::Star(GraphicComponent* gfx ,  TextureComponent* _Tex , XMFLOAT4X4 world) : GameObjects(gfx, "Star.obj")
	{
		_gfx = gfx;
		
	}

	void CalculateTransformation()  override
	{
		Timer t;
		XMMATRIX scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
		XMMATRIX translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x , ObjectRotation.y * t.time, ObjectRotation.z);


		XMStoreFloat4x4(&world, scale * translation * rotation);
	}

	void BindShaders() override
	{

		_pVertexShader = new VertexShader(_gfx->GetDevice(), _VS, L"DX11 Framework.fx");
		_pPixelShader = new PixelShader(_gfx->GetDevice(), _PS, L"DX11 Framework.fx");
		_VS = _pVertexShader->GetShader();
		_PS = _pPixelShader->GetShader();
		_gfx->InitialiseShaders(_VS, _PS);
	}
	void Initialise() 
	{
		
	
		
		//_pPixelShader = new PixelShaderComp(_gfx->GetDevice(), PS, L"DX11 Framework.fx");


	}
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader* _pVertexShader;
	PixelShader* _pPixelShader;
	GraphicComponent* _gfx;
};