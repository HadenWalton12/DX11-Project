#include "Application.h"
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

//Initalises Window Coordinates , Projection Matrix & View Matrix 
HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    Timer t;
    HRESULT hr = S_OK;
    if (FAILED(InitialiseWindow(hInstance, nCmdShow)))
    {
        return E_FAIL;
    }



    RECT rc;
    GetClientRect(_hWnd, &rc);

    //Pass calulated values , gives us window coordinates
    _WindowWidth = rc.right - rc.left;
    _WindowHeight = rc.bottom - rc.top;
    
    _pDX11 = new DX(_WindowWidth, _WindowHeight, _hWnd);
    _Tex = new TextureComponent();

    //InitialiseDevice , Assist creating core graphical components.
    _pDX11->InitialiseDevice();

    _StaticDefaultCamera = new StaticDefaultCamera();
    _pRenderCommands = new RenderCommands(_pDX11->_pDevice, _pDX11->_pDeviceContext, _StaticDefaultCamera, _pDX11->_pConstantBuffer);
    
    _star = new Star(_pRenderCommands, _Tex , _pDX11);
    _GameObjects.push_back(_star);
   
    _star->CreateTexture(L"Crate_COLOR.dds");



    
    return S_OK;
}

HRESULT Application::InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
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
    wcex.hCursor = LoadCursor(NULL, NULL);
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
    _hWnd = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

    //Check if Window did create.
    if (!_hWnd)
    {
        return E_FAIL;
    }

    ShowWindow(_hWnd, nCmdShow);
    return S_OK; 
}

Application::Application()
{
}

Application::~Application()
{
    Cleanup();
}

HRESULT Application::Update()
{
    for (auto gameobject : _GameObjects)
    {
        gameobject->Update();
    }

    for (auto cameraobject : _CameraObjects)
    {
        cameraobject->UpdateCamera();

    }


    return S_OK;
}
void Application::Draw()
{
    
    _pRenderCommands->ClearRenderTarget(_pDX11->_pRenderTargetView , _pDX11->_pDepthStencilView);

    for each (GameObjects* object in _GameObjects)
    {
        object->Draw();
    }
    _pRenderCommands->SwapChainPresent(_pDX11->_pSwapChain);

}

void Application::Cleanup()
{
    delete(_pDX11);
    delete(_pRenderCommands);

    delete(_star);

    delete(_Tex);
    delete(_pPixelShader);
    delete(_pVertexShader);
    delete(_PS);
    delete(_VS);

    _GameObjects.clear();
    _CameraObjects.clear();

}

