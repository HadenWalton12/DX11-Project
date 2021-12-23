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
class Plane : public GameObjects
{
public:
	Plane::Plane(RenderCommands* render_command, TextureComponent* _Tex, DX* dx , InputComponent* input ) : GameObjects(render_command) 
	{
		_pDX11 = dx;
		_PlaneInput = input;
		_pRenderCommand = render_command;
		CameraPosition  = XMFLOAT3(0.0f, 5.0f, -5.0f);
		LoadMesh();
		_pPlaneTransform = new ObjectTranformation(&_PlaneWorld);
		_pPlaneTransform->SetTranslation(0.0f, 2.0f, 0.0f);
		_pPlaneTransform->SetScale(0.10f, 0.10f, 0.10f);
		_pPlaneTransform->SetRotation(0.0f, 0.0f, 0.0f);
	}
	MeshData LoadMesh() 
	{
		_mesh = OBJLoader::Load("Hercules.obj", _pRenderCommand->GetDevice());
		return _mesh;
	}
	void WorldTransformations() override
	{
		DIMOUSESTATE mouseCurrState;

		XMFLOAT3 ObjectTranslate = _pPlaneTransform->GetTranslate();
	
		BYTE keyboardState[256];

		_PlaneInput->DIKeyBoard->Acquire();
		_PlaneInput->DIMouse->Acquire();


		_PlaneInput->DIKeyBoard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

		//Forward
		if (keyboardState[DIK_UP] & 0x80)
		{

			ObjectTranslate.x += cos((90 + 180) * TO_RADIANS) / 5.0;
			ObjectTranslate.z -= sin((90 + 180) * TO_RADIANS) / 5.0;
			CameraPosition.x += cos((90 + 180) * TO_RADIANS) / 5.0;
			CameraPosition.z -= sin((90 + 180) * TO_RADIANS) / 5.0;
	
		}

		//Backwards
		if (keyboardState[DIK_DOWN] & 0x80)
		{
			ObjectTranslate.x += cos((90) * TO_RADIANS) / 5.0;
			ObjectTranslate.z -= sin((90) * TO_RADIANS) / 5.0f;

			CameraPosition.x += cos((90) * TO_RADIANS) / 5.0;
			CameraPosition.z -= sin((90) * TO_RADIANS) / 5.0f;
		}

		//Right
		if (keyboardState[DIK_RIGHT] & 0x80)
		{
			ObjectTranslate.x += cos((90 - 90) * TO_RADIANS) / 5.0;
			ObjectTranslate.z -= sin((90 - 90) * TO_RADIANS) / 5.0;
			CameraPosition.x += cos((90 - 90) * TO_RADIANS) / 5.0;
			CameraPosition.z -= sin((90 - 90) * TO_RADIANS) / 5.0;
		}

		//Left
		if (keyboardState[DIK_LEFT] & 0x80)
		{
			ObjectTranslate.x += cos((90 + 90) * TO_RADIANS) / 5.0;
			ObjectTranslate.z -= sin((90 + 90) * TO_RADIANS) / 5.0;
			CameraPosition.x += cos((90 + 90) * TO_RADIANS) / 5.0;
			CameraPosition.z -= sin((90 + 90) * TO_RADIANS) / 5.0;
		}
		_pPlaneTransform->SetTranslation(ObjectTranslate.x , ObjectTranslate.y , ObjectTranslate.z);
		_pPlaneTransform->CalculateWorldTransformation(_PlaneWorld);
		SetPosition(CameraPosition);
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
	XMFLOAT3 GetPosition()
	{
		return CameraPosition;
	}
	void SetPosition(XMFLOAT3 pos)
	{

		CameraPosition = pos;
	}

	Timer  t;
	XMFLOAT4X4 _PlaneWorld;
	XMFLOAT3 CameraPosition;
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