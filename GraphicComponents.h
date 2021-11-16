#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"

#include "DDSTextureLoader.h"
#include "ShaderComponent.h"
#include "TextureComponent.h"
#include "VertexStruct.h"
#include "MeshStruct.h"
#include "ConstantStruct.h"
#include "OBJLoader.h"

using namespace DirectX;


class GraphicComponents
{
//Private Functions
private:
	void InitialiseBuffers();
	void InitialiseViewport();
	void InitialiseSwapChain();

	void SwapChainPresent();


	HRESULT InitialiseRenderTarget();
	void ClearRenderTarget();
	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitialiseDevice();
//Private Members
private:
	float ClearColor[4] = { 0.0f, 1.0f, 0.0f, 0.0f }; // red,green,blue,

	HINSTANCE               _hInst;
	HWND                    _hWnd;




	D3D_FEATURE_LEVEL       _featureLevel;


	IDXGISwapChain* _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11Texture2D* _pCubeTexture;



	ID3D11DepthStencilView* _pDepthStencilView;
	ID3D11Texture2D* _pDepthStencilBuffer;
	ID3D11RasterizerState* _pRasterizerState;



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

	TextureComponent* TexComp;

	void Cleanup();

public:
	GraphicComponents();
	~GraphicComponents();
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	ID3D11DeviceContext*	 _pImmediateContext;
	ID3D11Buffer*			_pConstantBuffer;
	D3D_DRIVER_TYPE         _driverType;
	ID3D11Device*			 _pPD3Ddevice;
	XMFLOAT4X4				_world;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;
	void SwitchWireFrame();
	//Switch Method , change buffers to draw different shapes
	void SwitchIndex_VertexBuffer(ID3D11Buffer* VB, ID3D11Buffer* IB);
	void InitialiseLigthing();
	void SwitchSolid();
	void UpdateBuffer();

	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;
};

