#pragma once

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

//Allows us to easily call reference upon our DX naming conventions
using namespace DirectX;

//XMFLOAT3 - Describes 3DVector , Consisting of Three Points (x,y ,z)
//XMFLOAT4 - Describes 4DVector , Consisting of Four Points (x)
//XMFLOAT4X4  - Structure that creates 4*4 Floating Point Matrix - Can be used to store XMMATRIX DATA
//and relevant matrix data within DX11

//Intialise Data Entries - Will be stored/referenced on Vertex Buffer
struct SimpleVertex
{
	XMFLOAT3 Pos;
    XMFLOAT3 Normal;

};

//Constant Buffer - This allows you to supply shader constants data to pipeline , data we want to continously supply 
//We store these within since our matrices update in realtime  as game state changes , our view as we may move around the screen
struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 DiffuseLight;

	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 AmbientLight;

	XMFLOAT4 SpecularMtrl;
	XMFLOAT4 SpecularLight;
	float SpecularPower;
	XMFLOAT4 EyePosW;

	XMFLOAT3 LightVecW;
};

class Application
{
private:

	//Used to initialize our window 
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	//Will be used to reference the type of drive that will be priortised use for DX11 application
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	//Virtual Representation of your video adapter(virtual representation of graphics card)
	ID3D11Device*           _pd3dDevice;
	//Applied as a device context that allows us to generate rendering commands to our device. Allowing us to manage our GPU and via that the rendering pipeline
	//Further used to manage all content relating to execution and creation of things to be executed onto our device
	ID3D11DeviceContext*    _pImmediateContext;
	//A series of buffers that allow us to take turn on buffers to render on , this variable is a pointer that references this process
	IDXGISwapChain*         _pSwapChain;
	//In order to render our application , we need to target our renderer , this is done so we can maintain the location in video memory to render into
	ID3D11RenderTargetView* _pRenderTargetView;
	
	/* Interface Management
			Objects related to controlling "Interfacing" data related to application ,
			controlling executed stages on  pipeline
	*/


	// Interfaces/manages vertex shader  that controls vertex-shader stage (stage on pipeline)
	ID3D11VertexShader*     _pVertexShader;			   
	//Interfaces/manages the pixel shader that controls pixel-shader stage (Stage on PipeLine) 
	ID3D11PixelShader*      _pPixelShader;
	
	//Input Layout holds definition of how to feed vertex data laid out in memory (Buffers)into input-assembler stage
	ID3D11InputLayout*      _pVertexLayout;
	
	//ID3D11Buffer* - This is a buffer interface that allows to access a buffer resource, this being unstructured memory
	//These buffers will allow us to store vertex or index data
	ID3D11Buffer* _pCubeVertexBuffer;
	ID3D11Buffer* _pTriangleVertexBuffer;
	ID3D11Buffer*           _pCubeIndexBuffer; 
	ID3D11Buffer*			_pTriangleIndexBuffer;
	//Will store Constant Data
	ID3D11Buffer*           _pConstantBuffer;
											  
	//Depth/Stencil Buffers - Used to create perception of depth between overlapping objects
	ID3D11DepthStencilView* _pDepthStencilView;

	//We can use this as texture render target or depth stencil resource , in this case a depth stencil resource
	ID3D11Texture2D* _pDepthStencilBuffer;
							
	//Can maniuplate rasterizerstate with pointer
	ID3D11RasterizerState* _wireFrame;
	//We can then use this to create the relevant world,view,projection matrices that we need.
	//We store this data in 4x4 Matrix to transpose/ mathmatically apply matrix mathmatic too.
	XMFLOAT4X4				_world , _world2, _world3, _world4 , _world5, _world6, _world7;
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
	/*HRESULT - WINDOWS DATATYPE THAT IS USED TO DESCRIBE ERROR OR WARNING - Making this our function type allows us to return error/warning messages
	previously not possible without such type
	Intialises our Windows Application*/

	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT CreateDevice();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT CreateShadersAndInputLayout();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();

	void Cleanup();

	UINT _WindowHeight;
	UINT _WindowWidth;

public:
	Application();
	~Application();
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	HRESULT Update();
	void Draw();
};

