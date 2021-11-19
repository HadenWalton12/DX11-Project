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
    _gfx->Initialise(hInstance, nCmdShow);
    _star = new Star(_gfx);
    _GameObjects.push_back(_star);
    _star->CreateTexture(L"Crate_COLOR.dds");

    return S_OK;
}



HRESULT Application::Update()
{

    HRESULT hr = S_OK;
    _gfx->InitialiseSolid();
    /*

    // Update our time
    static float t = 5.0f;


    if (_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
        t += (float)XM_PI * 0.0125f;
    }
    else
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();

        if (dwTimeStart == 0)
            dwTimeStart = dwTimeCur;

        t = (dwTimeCur - dwTimeStart) / 1000.0f;
    }

    _gTime = t;

   
    //Sun
    XMStoreFloat4x4(&_world, XMMatrixRotationY(t) * XMMatrixTranslation(0.0f, 0.0f, 0.0f));
    //Planets
    XMStoreFloat4x4(&_world2, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
   XMStoreFloat4x4(&_world4, XMMatrixScaling(0.75f, 0.75f, 0.75f) * XMMatrixRotationX(t) * XMMatrixTranslation(0.0f, 1.2f + cos(t) * 5, 0.0f + sin(t) * 5));
    //Moons
   XMStoreFloat4x4(&_world3, XMMatrixScaling(0.25f, 0.25f, 0.25f) * XMMatrixTranslation(-1.2f - cos(t) * 5, 0.0f - sin(t) * 5, 0.0f));
   XMStoreFloat4x4(&_world5, XMMatrixTranslation(0.0f, -2.0f, -1.0f));
  
    XMStoreFloat4x4(&objTestWorld, XMMatrixRotationY(t) * XMMatrixTranslation(4.0f, 0.0f, 0.0f));
    
    D3D11_RASTERIZER_DESC rastDesc;
    if (GetAsyncKeyState(VK_DOWN))
    {
        //Changes rasterizer stage (how we visually convert world to 2D texels) to fill mode, showing full normal object
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = 
    }
    else if (GetAsyncKeyState(VK_UP))
    {
        //Changes rasterizer state to wireframe mode
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_WIREFRAME;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);

    }
    _pImmediateContext->RSSetState(_wireFrame);
    */
    return S_OK;
}

void Application::Draw()
{


    _gfx->ClearBuffer();
    for (auto& object : _GameObjects) {
        object->Draw();
    }
    _gfx->SwapChain();
    /*
    // Set vertex buffer  passed into input assembly stage
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    float ClearColor[4] = { 0.0f, 1.0f, 0.0f, 0.0f }; // red,green,blue,alpha
    //Clears RenderView , current buffer, used for swap chain
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
    //Clears current depthview , also used to update depth from next buffer in swapchain
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); //for the float value :Clear the depth buffer with this value. This value will be clamped between 0 and 1.
   
  
    _pImmediateContext->PSSetSamplers(0, 1, &_pSamplerLinear);
    
    XMMATRIX world = XMLoadFloat4x4(&_world);
    XMMATRIX view = XMLoadFloat4x4(&_view);
    XMMATRIX projection = XMLoadFloat4x4(&_projection);













    _pImmediateContext->PSSetShaderResources(0, 1, &_pTextureRV);
    _pImmediateContext->DrawIndexed(36, 0, 0);

    
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pTriangleVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pTriangleIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    world = XMLoadFloat4x4(&_world2);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);

 
    world = XMLoadFloat4x4(&_world3);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);

 
    world = XMLoadFloat4x4(&_world4);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);
   

    _pImmediateContext->IASetVertexBuffers(0, 1, &_pGridVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pGridIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    world = XMLoadFloat4x4(&_world5);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(150, 0, 0);
    

    _pImmediateContext->IASetVertexBuffers(0, 1, &objStarMeshData.VertexBuffer, &objStarMeshData.VBStride, &objStarMeshData.VBOffset);
    _pImmediateContext->IASetIndexBuffer(objStarMeshData.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    world = XMLoadFloat4x4(&objTestWorld);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(objStarMeshData.IndexCount, 0, 0);
    */

}