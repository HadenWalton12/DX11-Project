#include "ShaderComponent.h"

ShaderComponent::ShaderComponent()
{
    _pVertexShader = nullptr;
    _pPixelShader = nullptr;
    _pVertexLayout = nullptr;

}

ShaderComponent::~ShaderComponent(){}

HRESULT ShaderComponent::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
    //Used to return arbitrary-length data - In this instance it returns error messages
    ID3DBlob* pErrorBlob;

    //Compiles Shader From FIle
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr)
        {
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        }
        if (pErrorBlob)
        {
            pErrorBlob->Release();
        }
        return hr;
    }

    return S_OK;
}



void ShaderComponent::SetInputLayout(ID3D11InputLayout* layout , GraphicComponent* gfx)
{
    gfx->_pImmediateContext->IASetInputLayout(layout);
}

HRESULT ShaderComponent::CreateVertexShader(GraphicComponent* gfx)
{
    HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"The FX File Vertex Shader Cannot be Compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = gfx->GetDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Define the input layout for data entering the Vertex Buffer
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0 , DXGI_FORMAT_R32G32_FLOAT , 0 , 24 , D3D11_INPUT_PER_VERTEX_DATA , 0},
    };

    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout - Describes layout of input buffer data within input assembler stage.
    hr = gfx->GetDevice()->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
    {
        return hr;
    }


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