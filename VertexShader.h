#pragma once
#include "Bindable.h"

class Shaders : public Bindable
{
public:
	Shaders(ID3D11Device* device, ID3D11DeviceContext* device_context) : Bindable(device, device_context)
	{}
	//Creates Vertex Shader , further compiles shader from file , this is done by compiling shader from fx file , then passing such data via local pPSBlob "Used to return data" to then pass into our VS Pointer , We also define the VertexShader Layout to which how we pass data into the shader (Tex , Normals , Vertexes) , this data will be later processed in PixelShader.
	HRESULT CreateVertexShader();

	//Creates Pixel Shader , further compiles shader from file , this is done by compiling shader from fx file , then passing such data via local pPSBlob "Used to return data" to then pass into our PS Pointer
	HRESULT CreatePixelShader();

	void SetShaders() override
	{
		_pDeviceContext->IASetInputLayout(_pVertexLayout);
		InitialiseShaders(_pVertexShader, _pPixelShader);


	}



	//Set the devicecontext to set the input Assemblers input layout
	void CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);


	//Private Objects
private:

	//Input Layout holds definition of how to feed vertex data laid out in memory (Buffers)into input-assembler stage
	ID3D11InputLayout* _pVertexLayout;

	// Interfaces/manages vertex shader  that controls vertex-shader stage (stage on pipeline)
	ID3D11VertexShader* _pVertexShader;

	//Interfaces/manages the pixel shader that controls pixel-shader stage (Stage on PipeLine) 
	ID3D11PixelShader* _pPixelShader;

};

