#include "ShaderComponent.h"

ShaderComponent::ShaderComponent()
{
    _pVertexShader = nullptr;
    _pPixelShader = nullptr;
    _pVertexLayout = nullptr;

}

ShaderComponent::~ShaderComponent(){}





void ShaderComponent::SetInputLayout(ID3D11InputLayout* layout , GraphicComponent* gfx)
{
    gfx->_pImmediateContext->IASetInputLayout(layout);
}

HRESULT ShaderComponent::CreateVertexShader(GraphicComponent* gfx)
{


  }
HRESULT ShaderComponent::CreatePixelShader(GraphicComponent* gfx)
{

    HRESULT hr;

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX File Pixel Shader Cannot be Compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = gfx->GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
    pPSBlob->Release();

    if (FAILED(hr))
    {
        return hr;
    }
}

void ShaderComponent::InitialiseShaders(ID3D11VertexShader* VS, ID3D11PixelShader* PS, GraphicComponent* gfx)
{
    gfx->_pImmediateContext->VSSetShader(VS, nullptr, 0);
    gfx->_pImmediateContext->VSSetConstantBuffers(0, 1, &gfx->_pConstantBuffer);
    gfx->_pImmediateContext->PSSetConstantBuffers(0, 1, &gfx->_pConstantBuffer);
    gfx->_pImmediateContext->PSSetShader(PS, nullptr, 0);
    gfx->_pImmediateContext->PSSetSamplers(0, 1, &gfx->_pSamplerLinear);
}
void ShaderComponent::ComposeShader(GraphicComponent* gfx)
{
    SetInputLayout(_pVertexLayout, gfx);
    InitialiseShaders(_pVertexShader, _pPixelShader, gfx);
}