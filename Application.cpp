#include "Application.h"
#include <xpolymorphic_allocator.h>

//Class Constructor - Initalizes pointer values used to initialize/create DX11 Application
Application::Application()
{
    //Intialise Window Variables
    _hInst = nullptr;
    _hWnd = nullptr;
   
    //D3D_DRIVER_TYPE - Paramater used to determine the choice of primary rendering device for application
    _driverType = D3D_DRIVER_TYPE_HARDWARE;
    _featureLevel = D3D_FEATURE_LEVEL_11_0;
    
    
    _pd3dDevice = nullptr;
    _pImmediateContext = nullptr;
    _pSwapChain = nullptr;
    _pRenderTargetView = nullptr;
    _pVertexShader = nullptr;
    _pPixelShader = nullptr;
    _pVertexLayout = nullptr;
    _pCubeVertexBuffer = nullptr;
    _pCubeIndexBuffer = nullptr;
    _pTriangleVertexBuffer = nullptr;
    _pTriangleIndexBuffer = nullptr;
    _pConstantBuffer = nullptr;
}

//Application destructor - Calls to cleanup to destruct pointer values.
Application::~Application()
{
    Cleanup();
}

/*
All windows based applications are event-driven , waiting for data to be passed from the system into the windows application
*/
//Application defining function , processes messages sent to the window
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{  
  
    //Used to paint the client area of a window owned by application.
    PAINTSTRUCT paint;
    //Used for windows based application graphics
    HDC hdc;

    //Determines theoutput of specific window queue messages.
    switch (message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &paint);
            EndPaint(hWnd, &paint);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYUP:

            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

//Initializes our window - 
HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    //WNDCLASSEX is the structure that contains the relevant members to registre our window , each member is seen below ,creating and designing our window to our needs 
    LPCWSTR p_class_name = L"ClassNameHere";
    WNDCLASSEX win_class = { 0 };
    
    
    
    
    win_class.cbSize = sizeof(WNDCLASSEX);
    win_class.style = CS_HREDRAW | CS_VREDRAW;
    win_class.lpfnWndProc = WndProc;
    win_class.cbClsExtra = 0;
    win_class.cbWndExtra = 0;
    win_class.hInstance = hInstance;
    win_class.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    win_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    win_class.lpszMenuName = nullptr;
    win_class.lpszClassName = p_class_name;
    win_class.hIconSm = LoadIcon(win_class.hInstance, (LPCTSTR)IDI_TUTORIAL1);
   
   
    if (!RegisterClassEx(&win_class))
    {
        return E_FAIL;
    }
    
    
    // Creates window instance
    _hInst = hInstance;

    //Creates Window
    _hWnd = CreateWindow(p_class_name, L"DX11 Framework",
        WS_OVERLAPPEDWINDOW|
        CW_USEDEFAULT| CW_USEDEFAULT, 600, 400,  640,  480 , nullptr, nullptr, hInstance,
        nullptr);
    
    
    //Error Method - Checks if Window was created 
    if (!_hWnd)
    {
        return E_FAIL;
    }
    
    
    ShowWindow(_hWnd, SW_SHOW);

    //Return Correct Error Method
    return S_OK;
}



//Drawing Method  - Calls upon filled values 
// - Specify Buffers To Execute
// - 
void Application::Draw()
{
    //Create Constant Buffer variable , in reference to struct
    ConstantBuffer constantbuff;
    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    // Renders a triangle - Calls upon ConstantBuffers(Stores View/Projection/World Matrix - Used for transformation pipeline) 
    //Calls Vertex/Pixel Shaders - Using stored data to translate with ^^ to render triangle
    _pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);
    _pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
    _pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
    _pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);


    //Initalize Local View,Projection & World Matrixes to make them equal the adjacent ones - For drawing purposes , using drawn values passed into global versions to be further processed
    XMMATRIX view = XMLoadFloat4x4(&_view);
    XMMATRIX projection = XMLoadFloat4x4(&_projection);
    XMMATRIX world = XMLoadFloat4x4(&_world);


    // Clear the back buffer  - Ready to perform and redraw next frame in sequence
    float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // red,green,blue,alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
    //Initalizes and creates our depth stencil view , simulating depth among 3D scene
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
        
    //Call reference to constbuff , Passing Local Represents of these variables (makes constbuff members equal adjacent local versions) , transposing each matrix
    constantbuff.mWorld = XMMatrixTranspose(world);
    constantbuff.mView  =  XMMatrixTranspose(view);
    constantbuff.mProjection = XMMatrixTranspose(projection);



    // Set index buffer
    _pImmediateContext->IASetIndexBuffer(_pCubeIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pCubeVertexBuffer, &stride, &offset);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
    //Calls upon number of Indicies need drawing
    _pImmediateContext->DrawIndexed(36, 0, 0);

    // Set index buffer
    _pImmediateContext->IASetIndexBuffer(_pTriangleIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pTriangleVertexBuffer, &stride, &offset);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
    //Creates / Initlizaes , Draws and renders our second cube object using same vertex data 
    world = XMLoadFloat4x4(&_world2);
    constantbuff.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);

    _pImmediateContext->DrawIndexed(18, 0, 0);


    world = XMLoadFloat4x4(&_world3);
    constantbuff.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);


    world = XMLoadFloat4x4(&_world4);
    constantbuff.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
    _pImmediateContext->DrawIndexed(36, 0, 0);



    world = XMLoadFloat4x4(&_world5);
    constantbuff.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);


    world = XMLoadFloat4x4(&_world6);
    constantbuff.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);


    world = XMLoadFloat4x4(&_world7);
    constantbuff.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
    _pImmediateContext->DrawIndexed(36, 0, 0);
    
    for (int i = 0; i < 100; i++)
    {
        world = XMLoadFloat4x4(&astroidbelt[i]);
        constantbuff.mWorld = XMMatrixTranspose(world);
        _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuff, 0, 0);
        _pImmediateContext->DrawIndexed(36, 0, 0);
    }
    
    
    // Present our back buffer to our front buffer
    _pSwapChain->Present(0, 0);
}


//Intialise 
HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{

    if (FAILED(InitWindow(hInstance, nCmdShow)))
	{
        return E_FAIL;
	}

    RECT rc;
    GetClientRect(_hWnd, &rc);
    _WindowWidth = rc.right - rc.left;
    _WindowHeight = rc.bottom - rc.top;

    if (FAILED(CreateDevice()))
    {
        Cleanup();

        return E_FAIL;
    }

	

    // Initialize the view matrix - Will determine our view projection when projection matrix is applied
	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f,-10.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    //Creates the view matrix - Determining our "camera" origin , storing the "eye , at , up" data in our 4x4 _view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(Eye, At, Up));

    // Initialize the projection matrix - Changing this with give us different projection
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT) _WindowHeight, 0.01f, 100.0f));

	return S_OK;
}

//Do not know its current purpose
HRESULT Application::CreateShadersAndInputLayout()
{
	HRESULT hr;


    //ID3DBlob Returns Data of a length - In our case we use this to comile the vertex shader , to create , we do this with pixel shader aswell
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
                   L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

	// Create the vertex shader - Used to process and and manipulate our vertexes stored in the buffer
    //The vertex shader takes data from vertex buffer , inputting and outputting a vertex, each vertex is pumped threw the vertex shader.
	hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

	if (FAILED(hr))
	{	
		pVSBlob->Release();
        return hr;
	}

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
                   L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

	// Create the pixel shader
	hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
	pPSBlob->Release();

    if (FAILED(hr))
        return hr;

    // Defines the input layout for data we wish to input into the input-assembler (This can be seen as a reference in vertex buffer )
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(layout);

    // Create the input layout - The layout of the data inputted into input_assembler - the be outputted
	hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
                                        pVSBlob->GetBufferSize(), &_pVertexLayout);
	pVSBlob->Release();

	if (FAILED(hr))
        return hr;

    // Set the input layout
    _pImmediateContext->IASetInputLayout(_pVertexLayout);

	return hr;
}


//Creates Application Vertex Buffer - (Vertex Buffer)
HRESULT Application::CreateVertexBuffer()
{
    HRESULT hr;

    // Create Vertex Data - Will be Stored in buffer
    SimpleVertex CubeStruct[] =
    {     // Vertex/Point Desc        //Colour decsription for point
        { XMFLOAT3(-1.0f,1.0f,0.0f)  ,XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)  },   // 0
        { XMFLOAT3(1.0f,1.0f,0.0f)  , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },   // 1 
        { XMFLOAT3(-1.0f,-1.0f,0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)  },   // 2 
        { XMFLOAT3(1.0f,-1.0f,0.0f) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },   // 3
        { XMFLOAT3(-1.0f,-1.0f,2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },   // 4
        { XMFLOAT3(1.0f,-1.0f,2.0f) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },   // 5 
        { XMFLOAT3(1.0f,1.0f,2.0f)  , XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },   // 6
        { XMFLOAT3(-1.0f, 1.0f,2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },   // 7
    };

    // Create Vertex Data - Will be Stored in buffer
    SimpleVertex TrianglePyramidStruct[] =
    {     // Vertex/Point Desc        //Colour decsription for point
         { XMFLOAT3(0.0f , 0.0f , 2.0f), XMFLOAT4(1.0f , 0.0f , 0.0f , 0.0f) }, //0 
         { XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f) }, // 1
         { XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f) }, // 2
         { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f) }, // 3
         { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f) }, // 4
    };

    //A struct that describes Buffer Resource - Our case describing Vertex Buffer
    D3D11_BUFFER_DESC Trianglebufferdescription;
	ZeroMemory(&Trianglebufferdescription, sizeof(Trianglebufferdescription));
   
    //Describe Vertex Buffer
    Trianglebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Trianglebufferdescription.ByteWidth = sizeof(SimpleVertex) * 5;
    Trianglebufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Trianglebufferdescription.CPUAccessFlags = 0;

    D3D11_BUFFER_DESC Cubebufferdescription;
    ZeroMemory(&Cubebufferdescription, sizeof(Cubebufferdescription));

    //Describe Vertex Buffer
    Cubebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Cubebufferdescription.ByteWidth = sizeof(SimpleVertex) * 8;
    Cubebufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Cubebufferdescription.CPUAccessFlags = 0;
  

    //Specifies data being used - Used in the process of creating buffers
    D3D11_SUBRESOURCE_DATA InitTriangleData;
	ZeroMemory(&InitTriangleData, sizeof(InitTriangleData));
    InitTriangleData.pSysMem = TrianglePyramidStruct;

    D3D11_SUBRESOURCE_DATA InitCubeData;
    ZeroMemory(&InitCubeData, sizeof(InitCubeData));
    InitCubeData.pSysMem = CubeStruct;
    //Call Our Device to create our vertex buffer , passing bufferdesc , intializing vetex buffer , then passing our vertexbuffer pointer (will store and manage our data)
    hr = _pd3dDevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeVertexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Trianglebufferdescription, &InitTriangleData, &_pTriangleVertexBuffer);

    //Fail Check Method
    if (FAILED(hr))
        return hr;

	return S_OK;
}

//This Creates Applications IndexBuffer - Same process of , describing , init and creating is same process as vertex buffer (reference comments inside "CreateVertexBuffer" to see similar process)
HRESULT Application::CreateIndexBuffer()
{
	HRESULT hr;

    // Create index buffer , stores reference to vertex points from "VertexData" Struct
    WORD cubeIndex[] =
    {
      //Front
        0,1,2,
        2,1,3,
       //Left
        3,1,6,
        3,6,5,
       //Right
        0,2,4,
        0,4,7,      
       //Top
        1,0,7,
        1,7,6,
       //Bottom
        2,3,5,
        2,5,4,        
       //Back
        5,6,7,
        5,7,4
    };
    WORD TriangleIndex[] =
    {
     0,2,1,
     0,1,4,
     0,4,3,
     0,3,2,
     4,3,2,
     4,2,1,

    };
	D3D11_BUFFER_DESC Trianglebufferdescription;
	ZeroMemory(&Trianglebufferdescription, sizeof(Trianglebufferdescription));

    Trianglebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Trianglebufferdescription.ByteWidth = sizeof(WORD) * 18;
    Trianglebufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Trianglebufferdescription.CPUAccessFlags = 0;

    D3D11_BUFFER_DESC Cubebufferdescription;
    ZeroMemory(&Cubebufferdescription, sizeof(Cubebufferdescription));

    Cubebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Cubebufferdescription.ByteWidth = sizeof(WORD) * 36;
    Cubebufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Cubebufferdescription.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitTriangleData;
	ZeroMemory(&InitTriangleData, sizeof(InitTriangleData));
    InitTriangleData.pSysMem = TriangleIndex;

    D3D11_SUBRESOURCE_DATA InitCubeData;
    ZeroMemory(&InitCubeData, sizeof(InitCubeData));
    InitCubeData.pSysMem = cubeIndex;

    hr = _pd3dDevice->CreateBuffer(&Trianglebufferdescription, &InitTriangleData, &_pTriangleIndexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeIndexBuffer);



    if (FAILED (hr) )
        return hr;

	return S_OK;
}


HRESULT Application::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

        if (pErrorBlob) pErrorBlob->Release();

        return hr;
    }

    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

HRESULT Application::CreateDevice()
{
    HRESULT hr = S_OK;

    UINT createDeviceFlags = 0;

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = _WindowWidth;
    sd.BufferDesc.Height = _WindowHeight;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = _hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;


    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        _driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
                                           D3D11_SDK_VERSION, &sd, &_pSwapChain, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }

    if (FAILED(hr))
        return hr;

    D3D11_TEXTURE2D_DESC depthStencilDesc;



    depthStencilDesc.Width = _WindowWidth;
    depthStencilDesc.Height = _WindowHeight;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    _pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_pDepthStencilBuffer);
    _pd3dDevice->CreateDepthStencilView(_pDepthStencilBuffer, nullptr, &_pDepthStencilView);


    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
    {
        return hr;
    }

    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED  (hr) )
    {
        return hr;
    }

    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);
   
    //D3D11_VIEWPORT - Viewport Structre - Allows us to define the dimensions for our viewport
    D3D11_VIEWPORT viewport;
    viewport.Width = (FLOAT)_WindowWidth;
    viewport.Height = (FLOAT)_WindowHeight;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    _pImmediateContext->RSSetViewports(1, &viewport);

	CreateShadersAndInputLayout();
	CreateVertexBuffer();

	CreateIndexBuffer();


    // Set primitive topology - 
    _pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBuffer);



    if (FAILED(hr))
    {
        return hr;
    }


    //Will describe conditions for rasterizer stage of pipeline
    D3D11_RASTERIZER_DESC rastDesc;

    ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
    rastDesc.FillMode = D3D11_FILL_WIREFRAME;
    rastDesc.CullMode = D3D11_CULL_NONE;
    hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);

    _pImmediateContext->RSSetState(_wireFrame);


    return S_OK;
}

//Clears all values upon termination
void Application::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();
    if (_pConstantBuffer) _pConstantBuffer->Release();
    if (_pCubeVertexBuffer) _pCubeVertexBuffer->Release();
    if (_pCubeIndexBuffer) _pCubeIndexBuffer->Release();
    if (_pTriangleVertexBuffer) _pTriangleVertexBuffer->Release();
    if (_pTriangleIndexBuffer) _pTriangleIndexBuffer->Release();
    if (_pVertexLayout) _pVertexLayout->Release();
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pd3dDevice) _pd3dDevice->Release();
    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();
    if (_wireFrame) _wireFrame->Release();
}

HRESULT Application::Update()
{
    HRESULT hr = S_OK;

    // Update our time
    static float t = 0.0f;

    if (_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
    
    }
    else
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();

        if (dwTimeStart == 0)
            dwTimeStart = dwTimeCur;

        t = (dwTimeCur - dwTimeStart) / 1000.0f;
    }
        

    
     //Update Cube Positions
	
    //Sun
    XMStoreFloat4x4(&_world, XMMatrixRotationY(t) * XMMatrixTranslation(0.0f , 0.0f ,0.0f));
    //Planets
    XMStoreFloat4x4(&_world2, XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationX(t)*  XMMatrixTranslation(0.0f - cos(t) * 5, 0.0f - sin(t) * 5 , 0.0f));
    XMStoreFloat4x4(&_world4, XMMatrixScaling(0.75f, 0.75f, 0.75f) * XMMatrixRotationX(t) * XMMatrixTranslation(0.0f, 1.2f + cos(t) * 5, 0.0f + sin(t) * 5));
    //Moons
    XMStoreFloat4x4(&_world3, XMMatrixScaling(0.25f, 0.25f, 0.25f) * XMMatrixTranslation(-1.2f - cos(t) * 5, 0.0f - sin(t) * 5, 0.0f));
    XMStoreFloat4x4(&_world5, XMMatrixScaling(0.25f, 0.25f, 0.25f) * XMMatrixTranslation(0.0f, -1.2f + cos(t) * 5, 0.0f + sin(t) * 5));
    
    //Bad Astroid Belt
    for (int i = 0; i < 100; i++)
    {
        XMStoreFloat4x4(&astroidbelt[i], XMMatrixScaling(0.15f, 0.15f, 0.15f) * XMMatrixRotationX(t) * XMMatrixTranslation(rand() % 2 - cos(t) * 5 , 2 - sin(t) * 5, 1));
    }

    
    //
    D3D11_RASTERIZER_DESC rastDesc;
    if (GetAsyncKeyState(VK_DOWN))
    {
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);
    }
    else if (GetAsyncKeyState(VK_UP))
    {
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_WIREFRAME;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);


    }
    _pImmediateContext->RSSetState(_wireFrame);
    return S_OK;
}






