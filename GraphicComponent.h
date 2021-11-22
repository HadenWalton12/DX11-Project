#pragma once
#include "SimpleVertexStructure.h"
#include "LightingValuesStructure.h"
#include "ConstantStructure.h"

#include "OBJLoader.h"
#include "resource.h"
#include "DDSTextureLoader.h"


//Libraries used to create application  

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library


using namespace DirectX; //Use default DX11 Naming conventions

class GraphicComponent
{
public:
	
	GraphicComponent();											//Constructor - Initialises Class Objects	
	~GraphicComponent();										//Destructor - Clears Class Object values - Done by calling cleanup function



	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow);//Initialises Window , Creates Window - Defines Name , Properties of window (Width & Hight) , Shows Window
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);		//Calls InitialiseWindow / InitialiseDevice , calling them for application creation.

	ID3D11Buffer* _pConstantBuffer;								//Defines ConstantBuffer Storage 
	ID3D11SamplerState* _pSamplerLinear;						//Bind to any shader stage (VS / PS) , used to bind reference of texture sample operations - We bind to PixelShader to accomidate per-pixel lighting
		
	ID3D11Device* GetDevice();									//Gets "_pd3dDevice" - Needed for reference of executing shader & texture systems within Shader/Texture Components - Returns value of singular device.
	ID3D11Device* _pd3dDevice;									//Virtual Representation of Video Card , used to create resources for application , resources exuted using device context
	ID3D11DeviceContext* _pImmediateContext;					//Stores reference to DeviceContext , allow us to generate rendering commands to execute within application

	D3D_DRIVER_TYPE         _driverType;

	void SwapChainPresent();									//Executes SwapChain function - Builds upon the creation/initilasation of it , utilising the swapchain , accompany this with clearing/initialising render target (Render Target is back buffer that gets swapped with front to be rendered to screen), we use these to flip front/back buffer to draw scene screens without double buffering.
	void ClearRenderTarget();									//Clears RenderTarget (Buffer our scene was draw) , so the buffer is ready to be drawn on with next scene
	void UpdateConstantBuffer();								//Updates constant buffer values
	void InitialiseSolid();										//Changes Rasterizer State to solid
	void InitialiseWireFrame();									//Changes Rasterizer State to WireFrame


//Private Objects
private:

	HINSTANCE               _hInst;								//Used to specify instance which the class is registred					
	HWND                    _hWnd;								//Used to handle a window , part of Win32 API , crates window using window instance above.

	UINT _WindowHeight;											//Define window height
	UINT _WindowWidth;											//Define window width

	D3D_FEATURE_LEVEL       _featureLevel;						//Defines feature level targeted by the device pointer. Essentially defines the version of the DirectX API we want to use

	IDXGISwapChain*			_pSwapChain;						//Interface object used to implement one or more buffers for storing rendered data before presenting it as an output
	ID3D11RenderTargetView* _pRenderTargetView;					//Defines render target and access to sub-resources that can be accessed during rendering to a buffer ()
	ID3D11ShaderResourceView* _pTextureRV;						//Defines shader subresource that can be accessed during rendering , e.g constant buffer,  in our case a texture buffer bound to texture data.

	ID3D11DepthStencilView* _pDepthStencilView;					//Defines view resource that accesses a texture resource during depth stencil testing , Our depth data is bound to a texture object
	ID3D11Texture2D*		_pDepthStencilBuffer;				//2D texture interface manager , managing texel data (structured image data) , stores depth data , processed in DepthStencilView

	ID3D11RasterizerState* _RasterizerState;					//Holds interface description for rasterizer state - to be bound to rasterizer stage

	//Used for transformations
	XMFLOAT4X4				_world;									
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;

	//Holds background colour value
	float ClearColor[4] = { 0.0f,0.0f,1.0f,0.0f };

//Private Functions
private:

	HRESULT InitialiseSwapchain();								//Creates SwapChain Function - Refer to notes of what this is
	HRESULT InitialiseRenderTarget();							//Creates RenderTarget Function - Refer to notes of what this is

	void Cleanup();												//Cleans Member Object Values
	void InitialiseSampler();									//Creates Sampler  Function - Refer to notes of what this is
	void InitialiseDevice();									//Calls Graphical Components for application creation - Has to be in order disclosed , Function names are self-explanatory
	void InitialiseDepth();										//Creates DepthBuffer Function - Refer to notes of what this is
	void InitialiseViewport();									//Initialise View Region - Refer to notes of what this is
	void InitialiseConstantBuffer();							//Initialise Constant Buffer - Refer to notes of what this is
	





};

