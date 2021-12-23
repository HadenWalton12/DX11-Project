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

    XMFLOAT3 DynamicCameraPostion = XMFLOAT3(0.0f, 0.0f, -3.0f);
    XMFLOAT3 TopDownCameraPosition = XMFLOAT3(0.0f, 5.0f, 0.0f);
    XMFLOAT3 DefaultCameraPosition = XMFLOAT3(0.0f, 0.0f, -5.0f);
    XMFLOAT3 PlaneCameraPosition = XMFLOAT3(0.0f, 5.0f, 0.0f);

    XMFLOAT3 DefaultCameraDirection = XMFLOAT3(0.0f, 0.0f, 3.0f);
    XMFLOAT3 TopDownCameraDirection = XMFLOAT3(0.0f, -0.01f, 0.000001f);
    XMFLOAT3 PlaneCameraDirection = XMFLOAT3(0.0f, -0.01f, 0.000001f);


    _DynamicMovementCamera = new DynamicMovementCamera(DynamicCameraPostion, 0.5f, 0.1f , 0.0f);
    _StaticTopDownCamera = new StaticTopDownCamera(TopDownCameraPosition , TopDownCameraDirection);
    _StaticDefaultCamera = new StaticDefaultCamera(DefaultCameraPosition , DefaultCameraDirection);
    _PlaneCamera = new PlaneCamera(PlaneCameraPosition, PlaneCameraDirection);
    
    _CameraObjects.push_back(_DynamicMovementCamera);
    _CameraObjects.push_back(_StaticTopDownCamera);
    _CameraObjects.push_back(_StaticDefaultCamera);
    _CameraObjects.push_back(_PlaneCamera);

    //Initialise Input Device
    _Input = new InputComponent(hInstance , _DynamicMovementCamera , _PlaneCamera);



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


HRESULT Application::Update()
{
    Timer t;
    BYTE keyboardState[256];

 
    _Input->DIKeyBoard->Acquire();
    _Input->DIKeyBoard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

    _Input->DetectWASDMovement();
    _Input->DetectPlaneMovement( _plane , _plane->_pPlaneTransform->GetTranslate(), _plane->_pPlaneTransform->GetScale() , _plane->_pPlaneTransform->GetRotation());
   
    //Forward
    if (keyboardState[DIK_1] & 0x80)
    {
        _pRenderCommands->SwitchCamera(_StaticDefaultCamera);
    }
    
    if (keyboardState[DIK_2] & 0x80)
    {
        _pRenderCommands->SwitchCamera(_DynamicMovementCamera);  
    }
    if (keyboardState[DIK_3] & 0x80)
    {
        _pRenderCommands->SwitchCamera(_StaticTopDownCamera);
    }
    if (keyboardState[DIK_4] & 0x80)
    {
        _pRenderCommands->SwitchCamera(_PlaneCamera);
    }
   
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
    for (auto gameobject : _GameObjects)
    {
        gameobject->Draw();

    }
    _pRenderCommands->SwapChainPresent(_pDX11->_pSwapChain);

}

