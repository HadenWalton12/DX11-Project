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





    if (!InitDirectInput(hInstance))
    {
        MessageBox(0, L"Direct Input Initialization - Failed",
            L"Error", MB_OK);
            return 0;
    }

    //InitialiseDevice , Assist creating core graphical components.
    _pDX11->InitialiseDevice();
    
    _pRenderCommands = new RenderCommands(_pDX11->_pDevice, _pDX11->_pDeviceContext, _Camera , _pDX11->_pConstantBuffer);
    
    _star = new Star(_pRenderCommands, _Tex , _pDX11);
    _plane = new Plane(_pRenderCommands, _Tex, _pDX11);
    _Terrain = new Terrain(_pRenderCommands, _Tex, _pDX11);
    
    _GameObjects.push_back(_Terrain);
    _GameObjects.push_back(_star);
    _GameObjects.push_back(_plane);
  

    _Terrain->CreateTexture(L"Grass.dds");
    _star->CreateTexture(L"Crate_COLOR.dds");
    _plane->CreateTexture(L"Hercules_COLOR.dds");
    XMFLOAT3 Camera_Position = XMFLOAT3(0.0f, 0.0f, 3.0f);
    XMFLOAT3 Camera_Target = XMFLOAT3(0.0f, 0.0f, -1.0f);
    XMFLOAT3 Camera_Up = XMFLOAT3(0.0f, 1.0f, 0.0f);

  
    _Camera = new CameraComponent(Camera_Position, Camera_Target, Camera_Up, _WindowWidth, _WindowHeight, 0.01f, 100.0f);
 
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
bool Application::InitDirectInput(HINSTANCE hInstance)
{
    DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DirectInput, NULL);

    DirectInput->CreateDevice(GUID_SysKeyboard, &DIKeyBoard, NULL);

    DirectInput->CreateDevice(GUID_SysMouse, &DIMouse, NULL);

    DIKeyBoard->SetDataFormat(&c_dfDIKeyboard);
    DIKeyBoard->SetCooperativeLevel(NULL , DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    DIMouse->SetDataFormat(&c_dfDIMouse);
    DIMouse->SetCooperativeLevel(NULL, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
    return true;
}
void Application::DetectInput()
{

    XMFLOAT3 CameraPosition = _Camera->GetPosition();
    XMFLOAT3 CameraDirection = _Camera->GetDirection();
    DIMOUSESTATE mouseCurrState;

    BYTE keyboardState[256];

    DIKeyBoard->Acquire();
    DIMouse->Acquire();

    DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

    DIKeyBoard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

    //Forward
    if (keyboardState[DIK_W] & 0x80)
    {
        CameraPosition.z -= 0.001;
    }

    //Backwards
    if (keyboardState[DIK_S] & 0x80)
    {
        CameraPosition.z += 0.001;
    }

    //Right
    if (keyboardState[DIK_D] & 0x80)
    {
        CameraPosition.x -= 0.001;
    }

    //Left
    if (keyboardState[DIK_A] & 0x80)
    {
        CameraPosition.x += 0.001;
    }

    //Up
    if (keyboardState[DIK_SPACE] & 0x80)
    {
        CameraPosition.y += 0.1;
    }

    //Down
    if (keyboardState[DIK_LSHIFT] & 0x80)
    {
        CameraPosition.y -= 0.1;
    }

    //Look Vertical
    if (mouseCurrState.lY != mouseLastState.lY)
    {
        CameraDirection.y -= (mouseCurrState.lY * 0.01f);
    }

    //Look Horizontal
    if (mouseCurrState.lX != mouseLastState.lX)
    {
        CameraDirection.x -= (mouseCurrState.lX * 0.01f);
    }

    //Update 
    _Camera->SetDirection(CameraDirection);
    _Camera->SetPosition(CameraPosition);
 
 
}
HRESULT Application::Update()
{
    Timer t;
    _pRenderCommands->SwitchCamera(_Camera);
       DetectInput();
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

