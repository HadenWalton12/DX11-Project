#pragma once
#include "ObjectComponent.h"
#include "InputComponent.h"
class Sphere : public GameObjects
{
public:
	Sphere::Sphere(RenderCommands* render_command, TextureComponent* _Tex, DX* dx , InputComponent* input) : GameObjects(render_command)
	{
		_SphereInput = input;
		_pDX11 = dx;
		_pRenderCommand = render_command;
		LoadMesh();
		_pSphereTransform = new ObjectTranformation(&_SphereWorld);
		_pSphereTransform->SetTranslation(0.0f, 0.0f, 0.0f);
		_pSphereTransform->SetScale(1.0f, 1.0f, 1.0f);
		_pSphereTransform->SetRotation(0.0f, 0.0f, 0.0f);
	}

	void WorldTransformations() override
	{


		BYTE keyboardState[256];
		_SphereInput->DIKeyBoard->Acquire();
		_SphereInput->DIMouse->Acquire();
		_SphereInput->DIKeyBoard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
		XMFLOAT3 ObjectTranslate = _pSphereTransform->GetTranslate();
		//Rotate
			if (keyboardState[DIK_F3] & 0x80)
			{
				Timer t;

				ObjectTranslate.x = -1.2f + cos(t.gTime) * 5;
				ObjectTranslate.y = 0.0f;
				ObjectTranslate.z = 0.0f + sin(t.gTime) * 5;
	

			}


			_pSphereTransform->SetTranslation(ObjectTranslate.x, ObjectTranslate.y, ObjectTranslate.z);
			
			_pSphereTransform->CalculateWorldTransformation(_SphereWorld);

		SetWorld(_pSphereTransform->GetWorld());
	}
	MeshData LoadMesh()
	{
		_mesh = OBJLoader::Load("Sphere.obj", _pRenderCommand->GetDevice());
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



	Timer  t;
	InputComponent* _SphereInput;
	XMFLOAT4X4 _SphereWorld;
	ObjectTranformation* _pSphereTransform;
	EntityTransformation transformation;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	VertexShader* _pVertexShader;
	DX* _pDX11;
	PixelShader* _pPixelShader;
	RenderCommands* _pRenderCommand;
};