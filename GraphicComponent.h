#pragma once

#include "Structure.h"
#include "OBJLoader.h"
//Libraries used to create application 
//Makes it possible to create our window
#include <windows.h>
//Access to core DX functions 
#include <d3d11_1.h>
//Allows us to compile DX11 Code
#include <d3dcompiler.h>
//Math Library
#include <directxmath.h>
#include <directxcolors.h>
//Libraries used to create application 
//Makes it possible to create our window
#include <windows.h>
//Access to core DX functions 
#include <d3d11_1.h>
//Allows us to compile DX11 Code
#include <d3dcompiler.h>
//Math Library
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"



#include "DDSTextureLoader.h"
//Allows us to easily call reference upon our DX naming conventions
using namespace DirectX;
class GraphicComponent
{
public:
	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
		void SwitchDrawBuffers(ID3D11Buffer* VB , ID3D11Buffer* IB );
	//Virtual Representation of your video adapter(virtual representation of graphics card)
	ID3D11Device* _pd3dDevice;
	void InitialiseSolid();
	void InitialiseShaders(ID3D11VertexShader* VS, ID3D11PixelShader* PS);
	void SetInputLayout(ID3D11InputLayout* layout);
	GraphicComponent();
		void SwapChain();
	void ClearBuffer();
	void UpdateConstantBuffer();
	~GraphicComponent();
	void Draw(unsigned int indexCount);
	HRESULT CreateTexture(wchar_t* filepath, ID3D11ShaderResourceView** texture);
	void BindTextures(int startSlot, int count, std::vector<ID3D11ShaderResourceView*> textures);
	void ClearTexture();
	ID3D11Device* GetDevice();
private:
	float ClearColor[4] = { 0.0f,0.0f,1.0f,0.0f };

	//Used to initialize our window 
	HINSTANCE               _hInst;
	HWND                    _hWnd;

	UINT _WindowHeight;
	UINT _WindowWidth;
	
	//Will be used to reference the type of drive that will be priortised use for DX11 application
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;



	//Applied as a device context that allows us to generate rendering commands to our device. Allowing us to manage our GPU and via that the rendering pipeline
	//Further used to manage all content relating to execution and creation of things to be executed onto our device
	ID3D11DeviceContext* _pImmediateContext;
	//A series of buffers that allow us to take turn on buffers to render on , this variable is a pointer that references this process
	IDXGISwapChain* _pSwapChain;
	//In order to render our application , we need to target our renderer , this is done so we can maintain the location in video memory to render into
	ID3D11RenderTargetView* _pRenderTargetView;

	ID3D11Texture2D* _pCubeTexture;
	ID3D11ShaderResourceView* _pTextureRV = nullptr;
	ID3D11SamplerState* _pSamplerLinear = nullptr;


	//Will store Constant Data
	ID3D11Buffer* _pConstantBuffer;

	//Depth/Stencil Buffers - Used to create perception of depth between overlapping objects
	ID3D11DepthStencilView* _pDepthStencilView;

	//We can use this as texture render target or depth stencil resource , in this case a depth stencil resource
	ID3D11Texture2D* _pDepthStencilBuffer;

	//Can maniuplate rasterizerstate with pointer
	ID3D11RasterizerState* _RasterizerState;

	XMFLOAT4X4				_world;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;
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
private:
	HRESULT InitialiseDevice();
	
	void Cleanup();
	HRESULT InitialiseSwapchain();
	void InitialiseSampler();
	void InitialiseDepth();

	HRESULT InitialiseRenderTarget();
	void InitialiseViewport();
	void InitialiseConstantBuffer();
	void InitialiseWireFrame();




};

