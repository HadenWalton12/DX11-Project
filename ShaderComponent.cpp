#include "ShaderComponent.h"

#include "GraphicComponents.h"

ShaderComponent::ShaderComponent()
{
}

ShaderComponent::~ShaderComponent()
{
}
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

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

        if (pErrorBlob) pErrorBlob->Release();

        return hr;
    }

    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

void ShaderComponent::InitialiseShader(ID3D11VertexShader* VS, ID3D11PixelShader* PS , ID3D11Buffer* CB)
{
    _pGFXComponent->_pImmediateContext->VSSetShader(VS, nullptr, 0);
    _pGFXComponent->_pImmediateContext->VSSetConstantBuffers(0, 1, &CB);
    _pGFXComponent->_pImmediateContext->PSSetConstantBuffers(0, 1, &CB);
    _pGFXComponent->_pImmediateContext->PSSetShader(PS, nullptr, 0);

}



HRESULT ShaderComponent::CreateShadersandInputLayout()
{
    HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = _pPD3Ddevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = _pPD3Ddevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
    pPSBlob->Release();

    if (FAILED(hr))
        return hr;

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0 , DXGI_FORMAT_R32G32_FLOAT , 0 , 24 , D3D11_INPUT_PER_VERTEX_DATA , 0},

    };

    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = _pPD3Ddevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &_pShaderLayout);
    pVSBlob->Release();

    if (FAILED(hr))
    {
        return hr;
    }
    // Determines the input layout - How our data will need to be presented to our program.
    _pGFXComponent->_pImmediateContext->IASetInputLayout(_pShaderLayout);

    return hr;
}

void ShaderComponent::SetSampler(ID3D11SamplerState* sample)
{
    _pGFXComponent->_pImmediateContext->PSSetSamplers(0, 1, &sample);
}
