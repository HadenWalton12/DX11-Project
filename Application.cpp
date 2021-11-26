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

    _plane = new Plane(_gfx, _Shader, _Tex, _gfx->_world2);
    _star = new Star(_gfx, _Shader, _Tex, _gfx->_world);
    _sphere = new Sphere(_gfx, _Shader, _Tex, _gfx->_world3);
    

    _sphere->CreateTexture(L"Crate_COLOR.dds");
    _sphere->SetTranslation(0.0f, -5.0f, 0.0f);
    _sphere->SetRotation(0.0f, 1.0f, 0.0f);
    _sphere->SetScale(1.0f, 1.0f, 1.0f);
    _star->CreateTexture(L"Crate_COLOR.dds");
    _star->SetTranslation(0.0f , -5.0f , 0.0f);
    _star->SetRotation(0.0f, 1.0f , 0.0f);
    _star->SetScale(2.0f, 2.0f, 26.0f);
    _plane->CreateTexture(L"Hercules_COLOR.dds");
    _plane->SetTranslation(0.0f, 0.0f, 0.0f);
    _plane->SetRotation(0.0f, 1.0f * t.time, 0.0f);
    _plane->SetScale(0.1f, 0.1f, 0.1f);
    return S_OK;
}



HRESULT Application::Update()
{
    _plane->Update(_gfx);
    _star->Update(_gfx);
    _sphere->Update(_gfx);
    return S_OK;
}

void Application::Draw()
{

    _gfx->ClearRenderTarget();
    _sphere->Draw();
    _plane->Draw();
    _star->Draw();
    _gfx->SwapChainPresent();

}