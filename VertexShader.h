#pragma once

#include "ShaderCompiler.h"

class VertexShader
{
public:

    VertexShader(ID3D11Device* device, ID3D11VertexShader* vertex_shader, ID3D11DeviceContext* device_context,WCHAR* VS_PATH) : _pDevice(device), _VertexShader(vertex_shader) , _pDeviceContext(device_context)
    {
        _pShaderCompiler = new ShaderCompiler();
        CreateVertexShader(VS_PATH, vertex_shader);
    }

    ~VertexShader()
    {

        Cleanup();

    }
    HRESULT CreateVertexShader(WCHAR* VS_PATH, ID3D11VertexShader* vertex_shader)
    {
        HRESULT hr = S_OK;

        ID3D11InputLayout* vertex_layout;

        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        hr = _pShaderCompiler->CompileShaderFromFile(VS_PATH, "VS", "vs_4_0", &pVSBlob);

        //Check Error Method - Was the CompiledShaderFromFile Above correct?
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"The FX File Vertex Shader Cannot be Compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the vertex shader
        _pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &vertex_shader);

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
        _pDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &vertex_layout);
        pVSBlob->Release();
        if (FAILED(hr))
        {
            return hr;
        }
        _pDeviceContext->IASetInputLayout(vertex_layout);
        _VertexShader = vertex_shader;

    }

    void Cleanup()
    {
        delete(_VertexShader);
        delete(_pDevice);
        delete(_pDeviceContext);
        delete(_pShaderCompiler);
    }
    ID3D11VertexShader* GetShader()
    {
        return _VertexShader;

    }
private:
    ID3D11VertexShader* _VertexShader;
    ID3D11Device* _pDevice;
    ID3D11DeviceContext* _pDeviceContext;
    ShaderCompiler* _pShaderCompiler;
};