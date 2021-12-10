#pragma once
#include "Bindable.h"

#include <vector>

class VertexBuffer : public Bindable
{
public:

	VertexBuffer(ID3D11Device* device, ID3D11DeviceContext* device_context, std::vector<SimpleVertex>& vertices) :  Bindable(device, device_context)
	{

		//Pyramid Index Buffer Description
		D3D11_BUFFER_DESC VertexBufferDescrption;
		ZeroMemory(&VertexBufferDescrption, sizeof(VertexBufferDescrption));

		VertexBufferDescrption.Usage = D3D11_USAGE_DEFAULT;
		VertexBufferDescrption.ByteWidth = sizeof(SimpleVertex) * vertices.size();
		VertexBufferDescrption.BindFlags = D3D11_BIND_INDEX_BUFFER;
		VertexBufferDescrption.CPUAccessFlags = 0;


		//Specifies data being used - Used in the process of creating buffers , calls reference to relevant index struct (InitData variable equals TrianglePyramidIndex)
		D3D11_SUBRESOURCE_DATA VertexBufferData;
		ZeroMemory(&VertexBufferData, sizeof(VertexBufferData));
		VertexBufferData.pSysMem = vertices.data();

		_pd3dDevice->CreateBuffer(&VertexBufferDescrption, &VertexBufferData, &_pVertexBuffer);
	}
	//Release Vertex Buffer
	~VertexBuffer()
	{
		if (_pVertexBuffer)
		{
			_pVertexBuffer->Release();
		}
	}

	//Bind Index Buffer passed to pipeline - 
	void SetVertexBuffer() override
	{
		_pDeviceContext->IASetVertexBuffers(0 , 1, &_pVertexBuffer, &_Stride, &_Offset);
	}

	
private:
	ID3D11Buffer* _pVertexBuffer;
	UINT _Stride = sizeof(SimpleVertex);
	UINT _Offset = 0;

};

