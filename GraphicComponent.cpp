#include "GraphicComponent.h"

//Callback function , processes message sent to the window.
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

HRESULT GraphicComponent::InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
{
    //Register/Window class initialisation
    WNDCLASSEX wcex;

    //Register/Window Class definition
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
    
    //Check if class registration was correct
    if (!RegisterClassEx(&wcex))
    {
        return E_FAIL;
    }


    // Create window
    _hInst = hInstance;

    //Define window width/hight
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    //Create Window
    _hWnd = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,nullptr);
    
    //Check if Window did create.
    if (!_hWnd)
    {
    return E_FAIL;
    }

    ShowWindow(_hWnd, nCmdShow);
    return S_OK;
}

HRESULT GraphicComponent::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    LigthtingValues lightvalue;
    //FAILED - HRESULT Code Function - Checks if HRESULT function is less than zero 

    //Check Error Initialising method, InitialiseWindow function called, if HRESULT return = 0 , return E_FAIL. If false (InititaliseWindow executed correctly) , Continue with application creation.
    if (FAILED(InitialiseWindow(hInstance, nCmdShow)))
    {
        return E_FAIL;
    }

    RECT rc;
    
    GetClientRect(_hWnd, &rc);

    //Pass calulated values , gives us window coordinates
    _WindowWidth = rc.right - rc.left;
    _WindowHeight = rc.bottom - rc.top;

   //InitialiseDevice , Assist creating core graphical components.
    InitialiseDevice();


    // Initialize values of view matrix - Defines values of 4x4 View matrix 
    XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
    XMFLOAT4 temp;
    XMStoreFloat4(&lightvalue.EyePosW, Eye);
    XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);

    //Initalize view matrix
    XMStoreFloat4x4(&_view, XMMatrixLookAtLH(Eye, At, Up));

    // Initialize the projection matrix
    XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 100.0f));

    //Return if any check error methods were false
    return S_OK;
}
 
GraphicComponent::GraphicComponent()
{
    _hInst = nullptr;
    _hWnd = nullptr;
    _driverType = D3D_DRIVER_TYPE_NULL;
    _featureLevel = D3D_FEATURE_LEVEL_11_0;
    _pSwapChain = nullptr;
    _pRenderTargetView = nullptr;
    _pConstantBuffer = nullptr;
    _pd3dDevice = nullptr;
    _pImmediateContext = nullptr;

}

GraphicComponent::~GraphicComponent()
{
    //Call Cleanup function 
    Cleanup();
}

void GraphicComponent::InitialiseDevice()
{
   
    InitialiseSwapchain();
    InitialiseDepth();
    InitialiseRenderTarget();
    InitialiseWireFrame();
    InitialiseSolid();
    InitialiseViewport();
    InitialiseConstantBuffer();
    InitialiseSampler();




}


void GraphicComponent::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();
    if (_pConstantBuffer) _pConstantBuffer->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pd3dDevice) _pd3dDevice->Release();
    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();
    if (_RasterizerState) _RasterizerState->Release();


}

HRESULT GraphicComponent::InitialiseSwapchain()
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
    if (FAILED(hr))
        return hr;
}
void GraphicComponent::InitialiseSampler()
{
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

    _pd3dDevice->CreateSamplerState(&sampDesc, &_pSamplerLinear);

}


void GraphicComponent::InitialiseDepth()
{
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
}


HRESULT GraphicComponent::InitialiseRenderTarget()
{
    HRESULT hr;
    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
        return hr;
    
    //Describes back buffer
    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED(hr))
        return hr;
    
    //Changed it from nullptr to "_depthStencilView" cause now there is a depth/stencil view.
    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);
    // Set primitive topology - Determines the format of how we draw primitives onto our DX11 Scene
    _pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}


void GraphicComponent::ClearRenderTarget()
{
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}


void GraphicComponent::SwapChainPresent()
{
    _pSwapChain->Present(0, 0);
}


void GraphicComponent::InitialiseViewport()
{
    // Setup the viewport
    D3D11_VIEWPORT viewport;
    viewport.Width = (FLOAT)_WindowWidth;
    viewport.Height = (FLOAT)_WindowHeight;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    _pImmediateContext->RSSetViewports(1, &viewport);
}


void GraphicComponent::InitialiseConstantBuffer()
{
    // Create the constant buffer
    D3D11_BUFFER_DESC constantbufferdescription;
    ZeroMemory(&constantbufferdescription, sizeof(constantbufferdescription));
    //Describe Constant Buffer
    constantbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    constantbufferdescription.ByteWidth = sizeof(ConstantBuffer);
    constantbufferdescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantbufferdescription.CPUAccessFlags = 0;
    
    //Create Buffer - Using Description above , 3rd parameters assigns value to Constantbuffer buffer pointer.
    _pd3dDevice->CreateBuffer(&constantbufferdescription, nullptr, &_pConstantBuffer);  
}

void GraphicComponent::UpdateConstantBuffer(XMFLOAT4X4 world)
{
    // Initialize the world matrix
    XMStoreFloat4x4(&world, XMMatrixIdentity());

    ConstantBuffer constantbuffer;
    LigthtingValues lightvalue;
    XMMATRIX _world = XMLoadFloat4x4(&world);
    XMMATRIX view = XMLoadFloat4x4(&_view);
    XMMATRIX projection = XMLoadFloat4x4(&_projection);

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

    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);

}




ID3D11Device* GraphicComponent::GetDevice()
{
    return _pd3dDevice;
}

void GraphicComponent::InitialiseWireFrame()
{
    //Create wireframe description
    D3D11_RASTERIZER_DESC wireframe;
    ZeroMemory(&wireframe, sizeof(D3D11_RASTERIZER_DESC));

    //Describe Wireframe
    wireframe.FillMode = D3D11_FILL_WIREFRAME;
    wireframe.CullMode = D3D11_CULL_NONE;

    //Create wirefram rasterizer stage
    _pd3dDevice->CreateRasterizerState(&wireframe, &_RasterizerState);
}

void GraphicComponent::InitialiseSolid()
{
    //Create wireframe description
    D3D11_RASTERIZER_DESC solid;
    ZeroMemory(&solid, sizeof(D3D11_RASTERIZER_DESC));

    //Describe Wireframe
    solid.FillMode = D3D11_FILL_SOLID;
    solid.CullMode = D3D11_CULL_NONE;

    //Create wirefram rasterizer stage
    _pd3dDevice->CreateRasterizerState(&solid, &_RasterizerState);
}