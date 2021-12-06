#include "Application.h"
    
/*
        Windows based aplications are always event drive to the core , waiting for messages(events) to be passed into message queue

*/



//Class Constructor - Initalizing all default values.
Application::Application()
{


}

//Class Destructor - Calls cleanup , releases values.
Application::~Application()
{

}

//Initalises Window Coordinates , Projection Matrix & View Matrix 
HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    Timer t;
    HRESULT hr = S_OK;
    


    _gfx = new GraphicComponent(); 
    _Tex = new TextureComponent();
    _Shader = new ShaderComponent();
    _gfx->Initialise(hInstance, nCmdShow);

    if (!InitDirectInput(hInstance))
    {
        MessageBox(0, L"Direct Input Initialization - Failed",
            L"Error", MB_OK);
            return 0;
    }
    
     _plane = new Plane(_gfx, _Shader, _Tex , _gfx->_world2);
    _star = new Star(_gfx, _Shader, _Tex , _gfx->_world1);
 //   _sphere = new Sphere(_gfx, _Shader, _Tex, _world3);
    _GameObjects.push_back(_plane);
    _GameObjects.push_back(_star);

//_sphere->CreateTexture(L"Crate_COLOR.dds");
  //  _sphere->SetTranslation(0.0f, -5.0f, 0.0f);
  // _sphere->SetRotation(0.0f, 1.0f, 0.0f);
  // _sphere->SetScale(1.0f, 1.0f, 1.0f);
    _star->CreateTexture(L"Crate_COLOR.dds");
    _star->SetTranslation(0.0f , 0.0f , 0.0f);
    _star->SetScale(0.02f, 0.02f, 0.02f);

   _plane->CreateTexture(L"Hercules_COLOR.dds");
   _plane->SetTranslation(5.0f, 0.0f, 0.0f);
   _plane->SetRotation(0.0f, 1.0f, 0.0f);
   _plane->SetScale(0.1f, 0.1f, 0.1f);
   XMFLOAT3 Camera_Position = XMFLOAT3(0.0f, 0.0f, 1.0f);
   XMFLOAT3 Camera_Target = XMFLOAT3(0.0f, 0.0f, -1.0f);
   XMFLOAT3 Camera_Up = XMFLOAT3 (0.0f, 1.0f, 0.0f);
   _Camera = new CameraComponent(Camera_Position , Camera_Target , Camera_Up, _gfx->_WindowWidth, _gfx->_WindowHeight, 0.01f, 100.0f );

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
        CameraPosition.y += 0.001;
    }

    //Down
    if (keyboardState[DIK_LSHIFT] & 0x80)
    {
        CameraPosition.y -= 0.001;
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
    _star->SetRotation(0.0f, 1.0f , 0.0f);
  
       _gfx->SwitchCamera(_Camera);
       DetectInput();
    for (auto gameobject : _GameObjects)
    {
 
        gameobject->Update(_gfx);
    }
    _gfx->UpdateCamera();

    return S_OK;
}

void Application::Draw()
{

    _gfx->ClearRenderTarget();
    for (auto gameobject : _GameObjects)
    {
        gameobject->Draw();

    }
    _gfx->SwapChainPresent();

}
