#pragma once
///////////////////////////////////////////////////////////////////////////
/////////////////////////////// INDEX BUFFER //////////////////////////////
////CREATE NEW INSTANCE OF IB WHEN NEEDED TO BIND NEW DATA TO PIPELINE ////
///////////////////////////////////////////////////////////////////////////

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library


using namespace DirectX; //Use default DX11 Naming 

#include <vector>

class IndexBuffer
{
public:
	//Used for object creation and binding to render pipeline.
	IndexBuffer(ID3D11Device* device, ID3D11DeviceContext* device_context, std::vector<WORD>& index, ID3D11Buffer* index_buffer) : _pIndexBuffer(index_buffer), Index(index)
	{

		UINT index_count;
		D3D11_BUFFER_DESC IndexBufferDescrption;

		ZeroMemory(&IndexBufferDescrption, sizeof(IndexBufferDescrption));

		IndexBufferDescrption.Usage = D3D11_USAGE_DEFAULT;
		IndexBufferDescrption.ByteWidth = sizeof(WORD) * Index.size();
		IndexBufferDescrption.BindFlags = D3D11_BIND_INDEX_BUFFER;
		IndexBufferDescrption.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA IndexBufferData;
		ZeroMemory(&IndexBufferData, sizeof(IndexBufferData));
		IndexBufferData.pSysMem = Index.data();

		device->CreateBuffer(&IndexBufferDescrption, &IndexBufferData, &_pIndexBuffer);
	}
	ID3D11Buffer* GetIndexBuffer()
	{
		return _pIndexBuffer;
	}

	UINT GetIndexCount()
	{
		_IndexCount = Index.size();
		return _IndexCount;
	}

private:

	ID3D11Buffer* _pIndexBuffer;
	UINT _IndexCount;
	std::vector<WORD>Index;
};