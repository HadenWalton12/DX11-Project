#include "Application.h"
/*
        Windows based aplications are always event drive to the core , waiting for messages(events) to be passed into message queue

*/

//Processes the event messages from queue ,based on the messages , if contained in queue we can give it specfic function.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

//Class Constructor - Initalizing all default values.
Application::Application()
{
    _hInst = nullptr;
    _hWnd = nullptr;
    _driverType = D3D_DRIVER_TYPE_NULL;
    _featureLevel = D3D_FEATURE_LEVEL_11_0;
    _pd3dDevice = nullptr;
    _pImmediateContext = nullptr;
    _pSwapChain = nullptr;
    _pRenderTargetView = nullptr;
    _pVertexShader = nullptr;
    _pPixelShader = nullptr;
    _pVertexLayout = nullptr;
    _pTriangleVertexBuffer = nullptr;
    _pTriangleIndexBuffer = nullptr;
    _pConstantBuffer = nullptr;

}

//Class Destructor - Calls cleanup , releases values.
Application::~Application()
{
    Cleanup();
}

//Initalises Window Coordinates , Projection Matrix & View Matrix 
HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    //Check Error Methods - Did Windows Initialise correctly?
    if (FAILED(InitWindow(hInstance, nCmdShow)))
    {
        return E_FAIL;
    }

    RECT rc;
    //Call class window value , pass window values into local rect
    GetClientRect(_hWnd, &rc);

    //Pass calulated values , gives us window coordinates
    _WindowWidth = rc.right - rc.left;
    _WindowHeight = rc.bottom - rc.top;

    //Check Error Method - Did Device initalise correctly?
    if (FAILED(CreateDevice()))
    {
        Cleanup();

        return E_FAIL;
    }

    // Initialize the world matrix
    XMStoreFloat4x4(&_world, XMMatrixIdentity());

    // Initialize values of view matrix - Defines values of 4x4 View matrix 
    XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
    XMFLOAT4 temp;
         XMStoreFloat4(&EyePosW, Eye);
    XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);

    //Initalize view matrix
    XMStoreFloat4x4(&_view, XMMatrixLookAtLH(Eye, At, Up));

    // Initialize the projection matrix
    XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 100.0f));

    //Return if any check error methods were false
    return S_OK;
}

HRESULT Application::CreateShadersAndInputLayout()
{
    HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
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

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0 , DXGI_FORMAT_R32G32_FLOAT , 0 , 24 , D3D11_INPUT_PER_VERTEX_DATA , 0},

    };

    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &_pVertexLayout);
    pVSBlob->Release();

    if (FAILED(hr))
    {
        return hr;
    }
    // Determines the input layout - How our data will need to be presented to our program.
    _pImmediateContext->IASetInputLayout(_pVertexLayout);

    return hr;
}

//Describes Buffer Data, resources , then creates buffers with data local in this
HRESULT Application::CreateVertexBuffer()
{
    HRESULT hr;

    //Initalise Vertex Data to be stored in buffer

    SimpleVertex CubeStruct[] =
    {     // Vertex/Point Desc        //Colour decsription for point
        { XMFLOAT3(1.0f ,1.0f,-1.0f), XMFLOAT3(0.333333f, 0.666667f , -0.666667f) , XMFLOAT2(0.0f , 0.1f)},    // 0
        { XMFLOAT3(-1.0f,1.0f,-1.0f)  , XMFLOAT3(-0.816497f, 0.408248f, -0.408248f) ,  XMFLOAT2(1.0f , 1.0f)},      // 1 
        { XMFLOAT3(-1.0f,1.0f,1.0f), XMFLOAT3(-0.333333f, 0.666667f, 0.666667f), XMFLOAT2(0.0f , 1.0f)}, // 2 
        { XMFLOAT3(1.0f,1.0f,1.0f) , XMFLOAT3(0.816497f, 0.408248f, 0.408248f), XMFLOAT2(1.0f , 1.0f)},      // 3
        { XMFLOAT3(1.0f,-1.0f,-1.0f), XMFLOAT3(0.666667f, -0.666667f, -0.333333f), XMFLOAT2(0.0f , 0.0f)},    // 4
        { XMFLOAT3(-1.0f,-1.0f,-1.0f) , XMFLOAT3(-0.408248f, -0.408248f, -0.816497f), XMFLOAT2(1.0f , 0.0f)},     // 5 
        { XMFLOAT3(-1.0f,-1.0f,1.0f)  , XMFLOAT3(-0.666667f, -0.666667f, 0.333333f), XMFLOAT2(0.0f , 0.0f)},    // 6
        { XMFLOAT3(1.0f, -1.0f,1.0f), XMFLOAT3(0.408248f, -0.408248f, 0.816497f), XMFLOAT2(1.0f , 0.0f)},  // 7
    };
    SimpleVertex PyramidStruct[] =
    {
         { XMFLOAT3(0.0f , 0.0f , 2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},  //0 
         { XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},  // 1
         { XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},  // 2
         { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},  // 3
         { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},// 4
    };
    SimpleVertex GridStruct[625] =
    {

    };


    for (int row = 0; row < 10; row++)
    {

        for (int col = 0; col < 5; col++)
        {
            int index = row * 5 + col;
            GridStruct[index] = { XMFLOAT3((float)col , 0.0f , (float)row), XMFLOAT3(0.0f , 0.0f ,0.0f) };

        }

    }
    //D3D11_BUFFER_DESC - Struct that allows us to describe a buffers resource

    //Pyramid Vertex Buffer Description
    D3D11_BUFFER_DESC Pyrmidbufferdescription;
    ZeroMemory(&Pyrmidbufferdescription, sizeof(Pyrmidbufferdescription));

    //Describing Trianlge Vertex Data 
    Pyrmidbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Pyrmidbufferdescription.ByteWidth = sizeof(SimpleVertex) * 8;//Size of data contained inside buffer
    Pyrmidbufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Pyrmidbufferdescription.CPUAccessFlags = 0;

    //Cube Vertex  Buffer Description
    D3D11_BUFFER_DESC Cubebufferdescription;
    ZeroMemory(&Cubebufferdescription, sizeof(Cubebufferdescription));

    Cubebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Cubebufferdescription.ByteWidth = sizeof(SimpleVertex) * 8;
    Cubebufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Cubebufferdescription.CPUAccessFlags = 0;

    //Cube Vertex  Buffer Description
    D3D11_BUFFER_DESC Gridbufferdescription;
    ZeroMemory(&Gridbufferdescription, sizeof(Gridbufferdescription));

    Gridbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Gridbufferdescription.ByteWidth = sizeof(SimpleVertex) * 25;
    Gridbufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Gridbufferdescription.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitGridData;
    ZeroMemory(&InitGridData, sizeof(InitGridData));
    InitGridData.pSysMem = GridStruct;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant vertex struct (InitData variable equals PyramidStruct)
    D3D11_SUBRESOURCE_DATA InitTriangleData;
    ZeroMemory(&InitTriangleData, sizeof(InitTriangleData));
    InitTriangleData.pSysMem = PyramidStruct;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant vertex struct (InitData variable equals CubeStruct)
    D3D11_SUBRESOURCE_DATA InitCubeData;
    ZeroMemory(&InitCubeData, sizeof(InitCubeData));
    InitCubeData.pSysMem = CubeStruct;

    // Call device pointer , pass "CreateBuffer" function , parameter pass in relevant local data above (describe data and buffer resource) , then reference Buffer pointer
    hr = _pd3dDevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeVertexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Pyrmidbufferdescription, &InitTriangleData, &_pTriangleVertexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Gridbufferdescription, &InitGridData, &_pGridVertexBuffer);
    //Fail Check Method
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}
//Describes Buffer Data , resources , then creates the buffers with data local in this
HRESULT Application::CreateIndexBuffer()
{
    HRESULT hr;

    //Initalse Index data, to bestored in index buffer
    WORD CubeIndex[] =
    {
        //Front
          0,1,2,
          0,2,3,

          0,4,5,
          0,5,1,

          1,5,1,
          1,6,2,

          2,6,7,
          2,7,3,

          3,7,4,
          3,4,0,

          4,7,6,
          4,6,5,

    };
    WORD TrianglePyramidIndex[] =
    {

     0,2,1,
     0,1,4,
     0,4,3,
     0,3,2,
     4,3,2,
     4,2,1,

    };

    const int width = 5;
    const int height = 5;

    WORD Grid[(width - 1) * (height - 1) * 6];
    int tri_index = 0;
    int vertex_index = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j < width - 1 && i < height - 1)
            {

                //Check Error Statement // Checks if points are less or higher than our unesscary values on grid
                Grid[tri_index] = vertex_index;
                Grid[tri_index + 1] = vertex_index + width + 1;
                Grid[tri_index + 2] = vertex_index + width;

                Grid[tri_index + 3] = vertex_index + width + 1;
                Grid[tri_index + 4] = vertex_index;
                Grid[tri_index + 5] = vertex_index + 1;


                tri_index += 6;
            }
            vertex_index++;
        }


    }
    //D3D11_BUFFER_DESC - Struct that allows us to describe a buffers resource

    //Pyramid Index Buffer Description
    D3D11_BUFFER_DESC Pyramidbufferdescription;
    ZeroMemory(&Pyramidbufferdescription, sizeof(Pyramidbufferdescription));

    Pyramidbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Pyramidbufferdescription.ByteWidth = sizeof(WORD) * 18;
    Pyramidbufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Pyramidbufferdescription.CPUAccessFlags = 0;

    //Cube Index Buffer Description
    D3D11_BUFFER_DESC Cubebufferdescription;
    ZeroMemory(&Cubebufferdescription, sizeof(Cubebufferdescription));

    Cubebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Cubebufferdescription.ByteWidth = sizeof(WORD) * 36;
    Cubebufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Cubebufferdescription.CPUAccessFlags = 0;

    //Cube Index Buffer Description
    D3D11_BUFFER_DESC Gridbufferdescription;
    ZeroMemory(&Gridbufferdescription, sizeof(Gridbufferdescription));

    Gridbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Gridbufferdescription.ByteWidth = sizeof(WORD) * 175;
    Gridbufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Gridbufferdescription.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA GridCubeData;
    ZeroMemory(&GridCubeData, sizeof(GridCubeData));
    GridCubeData.pSysMem = Grid;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant index struct (InitData variable equals TrianglePyramidIndex)
    D3D11_SUBRESOURCE_DATA InitTriangleData;
    ZeroMemory(&InitTriangleData, sizeof(InitTriangleData));
    InitTriangleData.pSysMem = TrianglePyramidIndex;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant index struct (InitData variable equals CubeIndex)

    D3D11_SUBRESOURCE_DATA InitCubeData;
    ZeroMemory(&InitCubeData, sizeof(InitCubeData));
    InitCubeData.pSysMem = CubeIndex;


    // Call device pointer , pass "CreateBuffer" function , parameter pass in relevant local data above (describe data and buffer resource) , then reference Buffer pointer
    hr = _pd3dDevice->CreateBuffer(&Pyramidbufferdescription, &InitTriangleData, &_pTriangleIndexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeIndexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Gridbufferdescription, &GridCubeData, &_pGridIndexBuffer);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    _hInst = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!_hWnd)
        return E_FAIL;

    ShowWindow(_hWnd, nCmdShow);

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
    //Lists drivetypes (methods of communicating to application to hardware)
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    //Describes the DX11 versions used
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };


    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    //Create Swap Chain Description
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));

    //Describes Swap Chain
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

    // Create the sample state

    D3D11_SAMPLER_DESC sampDesc;

    ZeroMemory(&sampDesc, sizeof(sampDesc));

    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;






    //Creates Depth Stencil buffer descriptor
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    //Describing buffer descriptor
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

    //Creating depth/stencil buffer
    _pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_pDepthStencilBuffer);//Depth stencil buffer
    _pd3dDevice->CreateDepthStencilView(_pDepthStencilBuffer, nullptr, &_pDepthStencilView);//Depth stencil view

  

    if (FAILED(hr))
    {
        return hr;
    }

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
    {
        return hr;
    }

    hr = CreateDDSTextureFromFile(_pd3dDevice, L"Crate_COLOR.dds", nullptr, &_pTextureRV);
    if (FAILED(hr))
    {
        return hr;
    }
  
    //
    //Describes back buffer
    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED(hr))
    {
        return hr;
    }
    //Changed it from nullptr to "_depthStencilView" cause now there is a depth/stencil view.
    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);

    // Setup the viewport
    D3D11_VIEWPORT viewport;
    viewport.Width = (FLOAT)_WindowWidth;
    viewport.Height = (FLOAT)_WindowHeight;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    _pImmediateContext->RSSetViewports(1, &viewport);

    //Passes such functions to Create device
    CreateShadersAndInputLayout();
    CreateVertexBuffer();
    CreateIndexBuffer();

    // Set primitive topology - Determines the format of how we draw primitives onto our DX11 Scene
    _pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Create the constant buffer
    D3D11_BUFFER_DESC constantbufferdescription;
    ZeroMemory(&constantbufferdescription, sizeof(constantbufferdescription));

    //Describe Constant Buffer
    constantbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    constantbufferdescription.ByteWidth = sizeof(ConstantBuffer);
    constantbufferdescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantbufferdescription.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&constantbufferdescription, nullptr, &_pConstantBuffer);

    //Create wireframe description
    D3D11_RASTERIZER_DESC wireframe;
    ZeroMemory(&wireframe, sizeof(D3D11_RASTERIZER_DESC));

    //Describe Wireframe
    wireframe.FillMode = D3D11_FILL_WIREFRAME;
    wireframe.CullMode = D3D11_CULL_NONE;

    //Create wirefram rasterizer stage
    hr = _pd3dDevice->CreateRasterizerState(&wireframe, &_wireFrame);
  

    _pd3dDevice->CreateSamplerState(&sampDesc, &_pSamplerLinear);


    if (FAILED(hr))
    {
        return hr;
    }

    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

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
    static float t = 5.0f;


    if (_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
        t += (float)XM_PI * 0.0125f;
    }
    else
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();

        if (dwTimeStart == 0)
            dwTimeStart = dwTimeCur;

        t = (dwTimeCur - dwTimeStart) / 1000.0f;
    }

    _gTime = t;


    //Sun
    XMStoreFloat4x4(&_world, XMMatrixRotationY(t) * XMMatrixTranslation(0.0f, 0.0f, 0.0f));
    //Planets
    XMStoreFloat4x4(&_world2, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
   XMStoreFloat4x4(&_world4, XMMatrixScaling(0.75f, 0.75f, 0.75f) * XMMatrixRotationX(t) * XMMatrixTranslation(0.0f, 1.2f + cos(t) * 5, 0.0f + sin(t) * 5));
    //Moons
   XMStoreFloat4x4(&_world3, XMMatrixScaling(0.25f, 0.25f, 0.25f) * XMMatrixTranslation(-1.2f - cos(t) * 5, 0.0f - sin(t) * 5, 0.0f));
   XMStoreFloat4x4(&_world5, XMMatrixTranslation(0.0f, -2.0f, -1.0f));

    
    D3D11_RASTERIZER_DESC rastDesc;

    if (GetAsyncKeyState(VK_DOWN))
    {
        //Changes rasterizer stage (how we visually convert world to 2D texels) to fill mode, showing full normal object
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);
    }
    else if (GetAsyncKeyState(VK_UP))
    {
        //Changes rasterizer state to wireframe mode
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_WIREFRAME;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);

    }
    _pImmediateContext->RSSetState(_wireFrame);

    return S_OK;
}

void Application::Draw()
{

    light_direction = XMFLOAT3(2.5f, 0.0f, 4.0f);
    diffuse_material = XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f);
    diffuse_light = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.5f);
    ambient_light = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
    ambient_material = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
    specular_material = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
    specular_light = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    specular_power = 1.0f;
    EyePosW = XMFLOAT4(0.0f, 0.0f, -5.0f, 0.0f);
    // Set vertex buffer  passed into input assembly stage
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    float ClearColor[4] = { 0.0f, 1.0f, 0.0f, 0.0f }; // red,green,blue,alpha
    //Clears RenderView , current buffer, used for swap chain
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
    //Clears current depthview , also used to update depth from next buffer in swapchain
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); //for the float value :Clear the depth buffer with this value. This value will be clamped between 0 and 1.
   
  
    _pImmediateContext->PSSetSamplers(0, 1, &_pSamplerLinear);
    
    XMMATRIX world = XMLoadFloat4x4(&_world);
    XMMATRIX view = XMLoadFloat4x4(&_view);
    XMMATRIX projection = XMLoadFloat4x4(&_projection);


    //Create local constant buffer , making our constant buffer world/view/projection equal the local versions of above, which equal the global versions which were initalised in the "Initalised" function.
    ConstantBuffer constantbuffer;
    constantbuffer.mWorld = XMMatrixTranspose(world);
    constantbuffer.mView = XMMatrixTranspose(view);
    constantbuffer.mProjection = XMMatrixTranspose(projection);
  
    constantbuffer.LightVecW = light_direction;
    constantbuffer.DiffuseLight = diffuse_light;
    constantbuffer.DiffuseMtrl = diffuse_material;

    constantbuffer.AmbientLight = ambient_light;
    constantbuffer.AmbientMtrl = ambient_material;
    constantbuffer.EyePosW = EyePosW;
    constantbuffer.SpecularPower = specular_power;
    constantbuffer.SpecularLight = specular_light;
    constantbuffer.SpecularMtrl = specular_material;
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);

    _pImmediateContext->IASetVertexBuffers(0, 1, &_pCubeVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pCubeIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    //Call VertexShader pointer, initalising the pointer used for Pipeline
    _pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);

    //Call ConstantShader pointer, initalising the pointer used to feed consant data into vertex shader
    _pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
    //Call ConstantShader pointer, initalising the pointer used to feed consant data into pixel shader
    _pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
    //Call PixelShader pointer, initalising the pointer used for Pipeline
  
    _pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);
    //_pImmediateContext->PSSetShaderResources(0, 1, &_pTextureRV);
    //SImilar to above, update input buffers passed into InputAssembly Stage , will draw all objects below with this buffer data



    _pImmediateContext->PSSetShaderResources(0, 1, &_pTextureRV);

    _pImmediateContext->DrawIndexed(36, 0, 0);


    _pImmediateContext->IASetVertexBuffers(0, 1, &_pTriangleVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pTriangleIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    world = XMLoadFloat4x4(&_world2);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);

 
    world = XMLoadFloat4x4(&_world3);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);

 
    world = XMLoadFloat4x4(&_world4);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);
   

    _pImmediateContext->IASetVertexBuffers(0, 1, &_pGridVertexBuffer, &stride, &offset);
    // Set index buffer passed into input assembly stage
    _pImmediateContext->IASetIndexBuffer(_pGridIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    world = XMLoadFloat4x4(&_world5);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(150, 0, 0);
    

    

    //
    // Present our back buffer to our front buffer
    //
    _pSwapChain->Present(0, 0);
}