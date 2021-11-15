#include "GraphicComponents.h"











void GraphicComponents::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();
    if (_pConstantBuffer) _pConstantBuffer->Release();
    if (_pVertexLayout) _pVertexLayout->Release();
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pPD3Ddevice) _pPD3Ddevice->Release();
    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();
    if (_pWireFrame) _pWireFrame->Release();
}

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
    _pVertexLayout = nullptr;
    _pConstantBuffer = nullptr;
}

GraphicComponents::~GraphicComponents()
{
}
