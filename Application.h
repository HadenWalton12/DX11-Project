#pragma once
//http://www.directxtutorial.com/Lesson.aspx?lessonid=11-4-1
//Libraries used to create application
// 
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

//Intialise Data Entries - Will be stored/referenced on Vertex Buffer
struct SimpleVertex
{
    XMFLOAT3 Vertex; 
    XMFLOAT4 Colour;
};

//Constant Buffer - This allows you to supply shader constants data to pipeline , data we want to continously supply 
struct ConstantBuffer
{
	//We store these within since our matrices update in realtime  as game state changes , our view as we may move around the screen
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
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

	ID3D11DeviceContext*    _pImmediateContext;//Applied as a device context that allows us to generate rendering commands to our device. Allowing us to manage our GPU and via that the rendering pipeline.
	IDXGISwapChain*         _pSwapChain;//A series of buffers that allow us to take turn on buffers to render on , this variable is a pointer that references this process.
	

	//In order to render our application , we need to target our renderer , this is done so we can maintain the location in video memory to render into
	ID3D11RenderTargetView* _pRenderTargetView;
	
	//Interfaces to relevant context , controls the specfic stage it is bound too
	ID3D11VertexShader*     _pVertexShader;// Manages our vertex shader, controls vertex-shader stage
	ID3D11PixelShader*      _pPixelShader; //Managers our Pixel Shader , controlling pixel-shader stage
	ID3D11InputLayout*      _pVertexLayout;
	
	
	//ID3D11Buffer* - This is a buffer interface that allows to access a buffer resource, this being unstructured memory , these buffers will allow us to store vertex or index data
	ID3D11Buffer*           _pVertexBuffer; //Will store Vertex Data
	// Will store Index Data
	ID3D11Buffer*           _pIndexBuffer; 
	 //Will store Constant Data
	ID3D11Buffer*           _pConstantBuffer;
	
											  
											  
	//Depth/Stencil Buffers - Used to create perception of depth between overlapping objects
	ID3D11DepthStencilView* _depthStencilView;
	
	//We can use this as texture render target or depth stencil resource , in this case a depth stencil resource
	ID3D11Texture2D* _depthStencilBuffer;

											  
											  
    //XMFLOAT4X4  - Structure that creates a 4*4 Floating Point Matrix ,
	//we can then use this to create the relevant world,view,projection matrices that we need.
	XMFLOAT4X4              _world , _world2;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;

private:


	//HRESULT - WINDOWS DATATYPE THAT IS USED TO DESCRIBE ERROR OR WARNING - Making this our function type allows us to return error/warning messages , previously not possible without such type 
	//Intialises our Windows Application
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	
	
	HRESULT CreateDevice();
	//
	void Cleanup();
	
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	HRESULT CreateShadersAndInputLayout();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();

	//Defines Window Size
	UINT _WindowHeight;
	UINT _WindowWidth;

public:
	Application();
	~Application();

	//Initalises windows application
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	//Update Application real time
	void Update();

	//Drawing Method of application
	void Draw();
};

