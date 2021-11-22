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
    HRESULT hr = S_OK;
    _gfx = new GraphicComponent(); 
    _Tex = new TextureComponent();
    _Shader = new ShaderComponent();
    _gfx->Initialise(hInstance, nCmdShow);
    _star = new Star(_gfx , _Shader , _Tex);
    _GameObjects.push_back(_star);

    _star->CreateTexture(L"Crate_COLOR.dds");

   rotationValue = 0.0f;
    return S_OK;
}



HRESULT Application::Update()
{

    for (auto gameobject : _GameObjects)
    {
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