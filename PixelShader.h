#include "ShaderCompiler.h"

class PixelShader
{
public:

    PixelShader(ID3D11Device* device, ID3D11PixelShader* pixel_shader, WCHAR* PS_PATH) : _pDevice(device)
    {
        _pShaderCompiler = new ShaderCompiler();
        CreatePixelShader(pixel_shader, PS_PATH);

    }

    HRESULT CreatePixelShader(ID3D11PixelShader* pixel_shader, WCHAR* PS_PATH)
    {
        HRESULT hr;

        ID3D11PixelShader* pixel_shader;
        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        hr = _pShaderCompiler->CompileShaderFromFile(PS_PATH, "PS", "ps_4_0", &pPSBlob);

        //Check Error Method - Was the CompiledShaderFromFile Above correct?
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX File Pixel Shader Cannot be Compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = _pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &pixel_shader);
        pPSBlob->Release();

        if (FAILED(hr))
        {
            return hr;
        }



    }

private:

    ID3D11Device* _pDevice;
    ShaderCompiler* _pShaderCompiler;
};