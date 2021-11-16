#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>


using namespace DirectX;
class GraphicComponents;
class ShaderComponent
{
private:

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);	

	GraphicComponents*	_pGFXComponent;
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader*	_pPixelShader;
	ID3D11InputLayout* _pShaderLayout;
	ID3D11Device* _pPD3Ddevice;
public: 
	ShaderComponent();
	~ShaderComponent();
	HRESULT CreateShadersandInputLayout();

	void SetSampler(ID3D11SamplerState* sample);
	void InitialiseShader(ID3D11VertexShader* VS, ID3D11PixelShader* PS, ID3D11Buffer* CB);

};

