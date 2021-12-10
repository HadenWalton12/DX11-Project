#pragma once
#include "Bindable.h"

class Shaders : public Bindable
{
public:
	Shaders(ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11Buffer* CB , WCHAR* VS_path , WCHAR* PS_path) : Bindable(device, device_context) , _pConstantBuffer(CB)
	{
		CreateVertexShader(VS_path);
		CreatePixelShader(PS_path);
		SetShaders(_pVertexLayout, _pVertexShader , _pConstantBuffer, _pPixelShader);
	}
	//Creates Vertex Shader , further compiles shader from file , this is done by compiling shader from fx file , then passing such data via local pPSBlob "Used to return data" to then pass into our VS Pointer , We also define the VertexShader Layout to which how we pass data into the shader (Tex , Normals , Vertexes) , this data will be later processed in PixelShader.
	HRESULT CreateVertexShader(WCHAR* VS_path)
	{
        HRESULT hr = S_OK;

        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        hr = CompileShaderFromFile(VS_path, "VS", "vs_4_0", &pVSBlob);

        //Check Error Method - Was the CompiledShaderFromFile Above correct?
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"The FX File Vertex Shader Cannot be Compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the vertex shader
        _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

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
        _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &_pVertexLayout);
        pVSBlob->Release();
        if (FAILED(hr))
        {
            return hr;
        }


	}

	//Creates Pixel Shader , further compiles shader from file , this is done by compiling shader from fx file , then passing such data via local pPSBlob "Used to return data" to then pass into our PS Pointer
    HRESULT CreatePixelShader(WCHAR* PS_path)
    {
        HRESULT hr;

        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        hr = CompileShaderFromFile(PS_path, "PS", "ps_4_0", &pPSBlob);

        //Check Error Method - Was the CompiledShaderFromFile Above correct?
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX File Pixel Shader Cannot be Compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
        pPSBlob->Release();

        if (FAILED(hr))
        {
            return hr;
        }

    }

	void SetShaders(ID3D11InputLayout* VL , ID3D11VertexShader* VS , ID3D11Buffer* CB , ID3D11PixelShader* PS , ID3D11SamplerState* sampler) override
	{
		_pDeviceContext->IASetInputLayout(VL);
		_pDeviceContext->VSSetShader(VS, nullptr, 0);
		_pDeviceContext->VSSetConstantBuffers(0, 1, &CB);
		_pDeviceContext->PSSetConstantBuffers(0, 1, &CB);
		_pDeviceContext->PSSetShader(PS, nullptr, 0);
		_pDeviceContext->PSSetSamplers(0, 1, &sampler);


	}

	//Set the devicecontext to set the input Assemblers input layout
    HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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
        hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

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



	//Private Objects
private:

    ID3D11Buffer* _pConstantBuffer;
	ID3D11InputLayout* _pVertexLayout;
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;

};

