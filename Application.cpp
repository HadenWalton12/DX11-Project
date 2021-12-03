#include "Application.h"
#include <math.h>
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
    _star->SetScale(2.0f, 2.0f, 2.0f);

   _plane->CreateTexture(L"Hercules_COLOR.dds");
   _plane->SetTranslation(5.0f, 0.0f, 0.0f);
   _plane->SetRotation(0.0f, 1.0f, 0.0f);
   _plane->SetScale(0.1f, 0.1f, 0.1f);
   _Camera = new CameraComponent(  XMFLOAT3(0.0f, 0.0f, 4.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 3.0f, 0.0f), _gfx->_WindowWidth, _gfx->_WindowHeight, 0.01f, 100.0f );
   _Camera2 = new CameraComponent(XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 3.0f, 0.0f), _gfx->_WindowWidth, _gfx->_WindowHeight, 0.01f, 100.0f);
   return S_OK;
}



HRESULT Application::Update()
{
    Timer t;
    _star->SetRotation(0.0f, 1.0f , 0.0f);
    float moveforward = 0.0f;
        _gfx->SwitchCamera(_Camera);
        float speed = 1.0f * t.time / 1000;
        XMFLOAT3 CameraPos = _Camera->GetEye();
       //Forward
        if (GetKeyState(0x57))
    {
            _Camera->moveBackForward += speed;
   
   
    }
        //Back
    else if (GetKeyState(0x53))
    {
            _Camera->moveBackForward -= speed;
         

    }
        //Right
    else if (GetKeyState(0x44))
    {
        
            _Camera->moveLeftRight += speed;

    }
        //Left
    else if (GetKeyState(0x41))
    {
            _Camera->moveLeftRight -= speed;
       

    }

        _Camera->SetEye(CameraPos);
    for (auto gameobject : _GameObjects)
    {
        _gfx->UpdateCamera();
        gameobject->Update(_gfx);
    }


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
