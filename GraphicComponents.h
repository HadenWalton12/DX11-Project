#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "OBJLoader.h"
#include "resource.h"

using namespace DirectX;


class GraphicComponents
{
//Private Functions
private:
	void InitialiseLigthing();
	void InitialiseBuffers();
	void InitialiseDevice();

	void SwitchWireFrame();
	void SwitchSolid();

	//Switch Method , change buffers to draw different shapes
	void SwitchIndex_VertexBuffer(ID3D11Buffer* VB , ID3D11Buffer* IB);



//Private Members
private:
	
	HINSTANCE               _hInst;
	HWND                    _hWnd;

	ID3D11Device* _pPD3Ddevice;

	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;


	ID3D11DeviceContext* _pImmediateContext;
	IDXGISwapChain* _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11Texture2D* _pCubeTexture;
	ID3D11SamplerState* _pSamplerLinear = nullptr;

	ID3D11Buffer* _pConstantBuffer;
	ID3D11DepthStencilView* _pDepthStencilView;
	ID3D11Texture2D* _pDepthStencilBuffer;
	ID3D11RasterizerState* _pWireFrame;

	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;
	ID3D11ShaderResourceView* _pTextureRV = nullptr;

	XMFLOAT3 light_direction;
	
	XMFLOAT4 diffuse_material;
	XMFLOAT4 diffuse_light;
	
	XMFLOAT4 specular_material;
	XMFLOAT4 specular_light;
	
	XMFLOAT4 ambient_material;
	XMFLOAT4 ambient_light;
	float specular_power;
	
	XMFLOAT4 EyePosW;
	float _gTime;

	UINT _WindowHeight;
	UINT _WindowWidth;


	void Cleanup();

public:
	GraphicComponents();
	~GraphicComponents();
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
};

