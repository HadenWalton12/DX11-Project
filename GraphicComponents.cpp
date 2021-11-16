#include "GraphicComponents.h"


GraphicComponents::GraphicComponents()
{
    _hInst = nullptr;
    _hWnd = nullptr;
    _driverType = D3D_DRIVER_TYPE_NULL;
    _featureLevel = D3D_FEATURE_LEVEL_11_0;
    _pPD3Ddevice = nullptr;
    _pImmediateContext = nullptr;
    _pSwapChain = nullptr;
    _pRenderTargetView = nullptr;
    _pVertexShader = nullptr;
    _pPixelShader = nullptr;

    _pConstantBuffer = nullptr;
}

GraphicComponents::~GraphicComponents()
{
}

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

HRESULT GraphicComponents::InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
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


HRESULT GraphicComponents::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    //Check Error Methods - Did Windows Initialise correctly?
    if (FAILED(InitialiseWindow(hInstance, nCmdShow)))
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
    if (FAILED(InitialiseDevice()))
    {
        Cleanup();

        return E_FAIL;
    }

   /*
    // Initialize the world matrix

    //objStarMeshData = OBJLoader::Load("star.obj", _pd3dDevice);
    
    */
    InitialiseLigthing();
    //Return if any check error methods were false
    return S_OK;
}

void GraphicComponents::InitialiseLigthing()
{
    ConstantBuffer constantbuffer;

    light_direction = XMFLOAT3(2.5f, 0.0f, 4.0f);
    diffuse_material = XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f);
    diffuse_light = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.5f);
    ambient_light = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
    ambient_material = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
    specular_material = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
    specular_light = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    specular_power = 1.0f;
    EyePosW = XMFLOAT4(0.0f, 0.0f, -5.0f, 0.0f);

    constantbuffer.LightVecW = light_direction;
    constantbuffer.DiffuseLight = diffuse_light;
    constantbuffer.DiffuseMtrl = diffuse_material;

    constantbuffer.AmbientLight = ambient_light;
    constantbuffer.AmbientMtrl = ambient_material;
    constantbuffer.EyePosW = EyePosW;
    constantbuffer.SpecularPower = specular_power;
    constantbuffer.SpecularLight = specular_light;
    constantbuffer.SpecularMtrl = specular_material;
}

void GraphicComponents::InitialiseBuffers()
{
    ConstantBuffer constantbuffer;

    //Creates Depth Stencil buffer descriptor
    D3D11_TEXTURE2D_DESC DSDesc;
    //Describing buffer descriptor
    DSDesc.Width = _WindowWidth;
    DSDesc.Height = _WindowHeight;
    DSDesc.MipLevels = 1;
    DSDesc.ArraySize = 1;
    DSDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    DSDesc.SampleDesc.Count = 1;
    DSDesc.SampleDesc.Quality = 0;
    DSDesc.Usage = D3D11_USAGE_DEFAULT;
    DSDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    DSDesc.CPUAccessFlags = 0;
    DSDesc.MiscFlags = 0;



    // Create the constant buffer
    D3D11_BUFFER_DESC constantbufferdescription;
    ZeroMemory(&constantbufferdescription, sizeof(constantbufferdescription));
    //Describe Constant Buffer
    constantbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    constantbufferdescription.ByteWidth = sizeof(ConstantBuffer);
    constantbufferdescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantbufferdescription.CPUAccessFlags = 0;
    
  
    /*XMMATRIX world = XMLoadFloat4x4(&_world);
    XMMATRIX view = XMLoadFloat4x4(&_view);
    XMMATRIX projection = XMLoadFloat4x4(&_projection);

    constantbuffer.mWorld = XMMatrixTranspose(world);
    constantbuffer.mView = XMMatrixTranspose(view);
    constantbuffer.mProjection = XMMatrixTranspose(projection);
    */
    
    
    //Create ConstantBuffer
    _pPD3Ddevice->CreateBuffer(&constantbufferdescription, nullptr, &_pConstantBuffer);

    //Creating depth/stencil buffer
    _pPD3Ddevice->CreateTexture2D(&DSDesc, nullptr, &_pDepthStencilBuffer);//Depth stencil buffer
    _pPD3Ddevice->CreateDepthStencilView(_pDepthStencilBuffer, nullptr, &_pDepthStencilView);//Depth stencil view
}

void GraphicComponents::UpdateBuffer()
{
    ConstantBuffer constantbuffer;

    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
}


void GraphicComponents::InitialiseViewport()
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


HRESULT GraphicComponents::InitialiseRenderTarget()
{
    HRESULT hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
    {
        return hr;
    }

    //  hr = CreateDDSTextureFromFile(_pd3dDevice, L"Crate_COLOR.dds", nullptr, &_pTextureRV);
    if (FAILED(hr))
    {
        return hr;
    }

    //
    //Describes back buffer
    hr = _pPD3Ddevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED(hr))
    {
        return hr;
    }
    //Changed it from nullptr to "_depthStencilView" cause now there is a depth/stencil view.
    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);
    // Set primitive topology - Determines the format of how we draw primitives onto our DX11 Scene
    _pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void GraphicComponents::ClearRenderTarget()
{
    //Clears RenderView , current buffer, used for swap chain
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
    //Clears current depthview , also used to update depth from next buffer in swapchain
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); //for the float value :Clear the depth buffer with this value. This value will be clamped between 0 and 1.

}

HRESULT GraphicComponents::InitialiseDevice()
{
    HRESULT hr;


    InitialiseSwapChain();
    InitialiseBuffers();
    InitialiseRenderTarget();
    InitialiseViewport();
    TexComp->InitialiseSampler();
    //Passes such functions to Create device
    //CreateShadersAndInputLayout();
    //CreateVertexBuffer();
    //CreateIndexBuffer();

    return hr;
}

void GraphicComponents::InitialiseSwapChain()
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
    DXGI_SWAP_CHAIN_DESC SwapChainDescription;
    ZeroMemory(&SwapChainDescription, sizeof(SwapChainDescription));

    //Describes Swap Chain
    SwapChainDescription.BufferCount = 1;
    SwapChainDescription.BufferDesc.Width = _WindowWidth;
    SwapChainDescription.BufferDesc.Height = _WindowHeight;
    SwapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDescription.OutputWindow = _hWnd;
    SwapChainDescription.SampleDesc.Count = 1;
    SwapChainDescription.SampleDesc.Quality = 0;
    SwapChainDescription.Windowed = TRUE;

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        _driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &SwapChainDescription, &_pSwapChain, &_pPD3Ddevice, &_featureLevel, &_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }


}

void GraphicComponents::SwitchWireFrame()
{
    D3D11_RASTERIZER_DESC RastDesc;

    //Changes rasterizer state to wireframe mode
    ZeroMemory(&RastDesc, sizeof(D3D11_RASTERIZER_DESC));
    RastDesc.FillMode = D3D11_FILL_WIREFRAME;
    RastDesc.CullMode = D3D11_CULL_NONE;
    _pPD3Ddevice->CreateRasterizerState(&RastDesc, &_pRasterizerState);
    _pImmediateContext->RSSetState(_pRasterizerState);
}

void GraphicComponents::SwitchSolid()
{
    D3D11_RASTERIZER_DESC RastDesc;
    //Changes rasterizer stage (how we visually convert world to 2D texels) to fill mode, showing full normal object
    ZeroMemory(&RastDesc, sizeof(D3D11_RASTERIZER_DESC));
    RastDesc.FillMode = D3D11_FILL_SOLID;
    RastDesc.CullMode = D3D11_CULL_NONE;
    _pPD3Ddevice->CreateRasterizerState(&RastDesc, &_pRasterizerState);
    _pImmediateContext->RSSetState(_pRasterizerState);
    
}

void GraphicComponents::SwapChainPresent()
{
    //
    // Present our back buffer to our front buffer
    //
    _pSwapChain->Present(0, 0);
}

void GraphicComponents::SwitchIndex_VertexBuffer(ID3D11Buffer* VB, ID3D11Buffer* IB)
{
    // Set vertex buffer  passed into input assembly stage
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    _pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset) ;
    _pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}

void GraphicComponents::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();
    if (_pConstantBuffer) _pConstantBuffer->Release();
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pPD3Ddevice) _pPD3Ddevice->Release();
    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();
    if (_pRasterizerState) _pRasterizerState->Release();
}