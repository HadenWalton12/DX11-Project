#pragma once

//Used For Initialising DirectX FrameWork Components

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library
#include "ConstantStructure.h"
#include "LightingValuesStructure.h"
#include "CameraComponent.h"


using namespace DirectX; //Use default DX11 Naming conventions

class RenderCommands
{
public:

	RenderCommands(ID3D11Device* device , ID3D11DeviceContext* device_context , CameraComponent* camera , ID3D11Buffer* CB) : _pDevice(device) , _pDeviceContext(device_context), _Camera(camera) , _pConstantBuffer(CB)
	{


	}
	~RenderCommands()
	{



	}


	void  ClearRenderTarget(ID3D11RenderTargetView* target_view , ID3D11DepthStencilView* depth_view)
	{
		_pDeviceContext->ClearRenderTargetView(target_view, ClearColor);
		_pDeviceContext->ClearDepthStencilView(depth_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	void SwapChainPresent(IDXGISwapChain* swap_chain)
	{

		swap_chain->Present(0, 0);
	}

	void BindVertexShader(ID3D11VertexShader* vertex_shader)
	{
		_pDeviceContext->VSSetShader(vertex_shader, nullptr, 0);

	}

	void BindPixelShader(ID3D11PixelShader* pixel_shader)
	{
		_pDeviceContext->PSSetShader(pixel_shader, nullptr, 0);

	}
	void BindSampler(ID3D11SamplerState* sampler)
	{
		_pDeviceContext->PSSetSamplers(0, 1, &sampler);
	}

	void UpdateConstantBuffer(XMFLOAT4X4 world)
	{
		ConstantBuffer constantbuffer;
		LigthtingValues lightvalue;
		XMMATRIX _world = XMLoadFloat4x4(&world);
		XMMATRIX view = XMLoadFloat4x4(&_Camera->GetView());
		XMMATRIX projection = XMLoadFloat4x4(&_Camera->GetProjection());


		constantbuffer.mWorld = XMMatrixTranspose(_world);
		constantbuffer.mView = XMMatrixTranspose(view);
		constantbuffer.mProjection = XMMatrixTranspose(projection);

		constantbuffer.LightVecW = lightvalue.light_direction;
		constantbuffer.DiffuseLight = lightvalue.diffuse_light;
		constantbuffer.DiffuseMtrl = lightvalue.diffuse_material;
		constantbuffer.AmbientLight = lightvalue.ambient_light;
		constantbuffer.AmbientMtrl = lightvalue.ambient_material;
		constantbuffer.EyePosW = lightvalue.EyePosW;
		constantbuffer.SpecularPower = lightvalue.specular_power;
		constantbuffer.SpecularLight = lightvalue.specular_light;
		constantbuffer.SpecularMtrl = lightvalue.specular_material;

		_pDeviceContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
	}

	void SwitchCamera(CameraComponent* camera)
	{
		_Camera = camera;	
	}

	void UpdateCamera()
	{
		_Camera->Update();
	}

	ID3D11Device* GetDevice()
	{
		return _pDevice;

	}

	ID3D11DeviceContext* GetDeviceContext()
	{
		return _pDeviceContext;

	}
private:
	ID3D11Buffer* _pConstantBuffer;								//Defines ConstantBuffer Storage 

	CameraComponent* _Camera;
	ID3D11Device* _pDevice;
	ID3D11DeviceContext* _pDeviceContext;
	//Holds background colour value
	float ClearColor[4] = { 0.0f,0.0f,1.0f,0.0f };
};

