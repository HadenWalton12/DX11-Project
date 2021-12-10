#pragma once
#include "Bindable.h"

#include <vector>

class IndexBuffer : public Bindable
{
public:

	IndexBuffer(ID3D11Device* device, ID3D11DeviceContext* device_context , std::vector<WORD>&Index) : _IndexCount(Index.size()) , Bindable(device , device_context) 
	{

		//Pyramid Index Buffer Description
		D3D11_BUFFER_DESC IndexBufferDescrption;
		ZeroMemory(&IndexBufferDescrption, sizeof(IndexBufferDescrption));

		IndexBufferDescrption.Usage = D3D11_USAGE_DEFAULT;
		IndexBufferDescrption.ByteWidth = sizeof(WORD) * Index.size();
		IndexBufferDescrption.BindFlags = D3D11_BIND_INDEX_BUFFER;
		IndexBufferDescrption.CPUAccessFlags = 0;


		//Specifies data being used - Used in the process of creating buffers , calls reference to relevant index struct (InitData variable equals TrianglePyramidIndex)
		D3D11_SUBRESOURCE_DATA IndexBufferData;
		ZeroMemory(&IndexbufferData, sizeof(IndexBufferData));
		IndexBufferData.pSysMem = Index.data();

		_pd3dDevice->CreateBuffer(&IndexBufferDescrption, &IndexBufferData, &_pIndexBuffer);
	}
	//Release Index Buffer
	~IndexBuffer()
	{
		if (_pIndexBuffer)
		{
			_pIndexBuffer->Release();
		}
	}

	//Bind Index Buffer passed to pipeline - 
	void SetIndexBuffer() override
	{
		_pDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	}

	UINT GetIndexCount()
	{
		return _IndexCount;
	}
private:
	ID3D11Buffer* _pIndexBuffer;
	UINT _IndexCount;
};

