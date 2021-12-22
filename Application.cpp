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
    
    _pRenderCommands = new RenderCommands(_pDX11->_pDevice, _pDX11->_pDeviceContext, _StaticDefaultCamera, _pDX11->_pConstantBuffer);
    
    _star = new Star(_pRenderCommands, _Tex , _pDX11);
    _plane = new Plane(_pRenderCommands, _Tex, _pDX11);
    _Terrain = new Terrain(_pRenderCommands, _Tex, _pDX11);
    
    _GameObjects.push_back(_Terrain);
    _GameObjects.push_back(_star);
    _GameObjects.push_back(_plane);
  

    _Terrain->CreateTexture(L"Grass.dds");
    _star->CreateTexture(L"Crate_COLOR.dds");
    _plane->CreateTexture(L"Hercules_COLOR.dds");
    XMFLOAT3 DynamicCameraPostion = XMFLOAT3(0.0f, 5.0f, -3.0f);
    XMFLOAT3 TopDownCameraPosition = XMFLOAT3(0.0f, 5.0f, 0.0f);
    XMFLOAT3 DefaultCameraPosition = XMFLOAT3(0.0f, 0.0f, -3.0f);

    XMFLOAT3 DynamicCameraDirection = XMFLOAT3(0.0f, 0.0f, 3.0f);
    XMFLOAT3 DefaultCameraDirection = XMFLOAT3(0.0f, 0.5f, 0.0f);
    XMFLOAT3 TopDownCameraDirection = XMFLOAT3(0.0f, -0.01f, 0.000001f);

    XMFLOAT3 Camera_Up = XMFLOAT3(0.0f, 1.0f, 0.0f);


    _DynamicMovementCamera = new CameraComponent(DynamicCameraPostion, DynamicCameraDirection, Camera_Up, _WindowWidth, _WindowHeight, 0.01f, 100.0f);
    _StaticTopDownCamera = new CameraComponent(TopDownCameraPosition, TopDownCameraDirection, Camera_Up, _WindowWidth, _WindowHeight, 0.01f, 100.0f);
    _StaticDefaultCamera = new CameraComponent(DefaultCameraPosition, DefaultCameraDirection, Camera_Up, _WindowWidth, _WindowHeight, 0.01f, 100.0f);

    //Initialise Input Device
    _Input = new InputComponent(hInstance);

    //Set Initial Camera Instance
    _pRenderCommands->SetCamera(_StaticDefaultCamera);
    
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
    _hWnd = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

    //Check if Window did create.
    if (!_hWnd)
    {
        return E_FAIL;
    }

    ShowWindow(_hWnd, nCmdShow);
    return S_OK;
}


HRESULT Application::Update()
{
    Timer t;
    BYTE keyboardState[256];

    int key_instance = 0;
    _Input->DIKeyBoard->Acquire();
    _Input->DIKeyBoard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
    _Input->DetectWASDMovement(_DynamicMovementCamera);
    //Forward
    if (keyboardState[DIK_1] & 0x80)
    {
        _pRenderCommands->SwitchCamera(_StaticDefaultCamera);
        key_instance = 1;
    }
    
    if (keyboardState[DIK_2] & 0x80)
    {
        key_instance = 2;
        _pRenderCommands->SwitchCamera(_DynamicMovementCamera);   
    }
    if (keyboardState[DIK_3] & 0x80)
    {
        _pRenderCommands->SwitchCamera(_StaticTopDownCamera);
        key_instance = 3;
    }
    if (keyboardState[DIK_4] & 0x80)
    {
    }
   
 
   
    for (auto gameobject : _GameObjects)
    {
        gameobject->Update();
    }

    _pRenderCommands->UpdateCamera();

    return S_OK;
}
void Application::Draw()
{

    _pRenderCommands->ClearRenderTarget(_pDX11->_pRenderTargetView , _pDX11->_pDepthStencilView);
    for (auto gameobject : _GameObjects)
    {
        gameobject->Draw();

    }
    _pRenderCommands->SwapChainPresent(_pDX11->_pSwapChain);

}

