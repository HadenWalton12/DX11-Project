///////////////////////////////////////////////////////////////////////////
//////////////////////////////  VERTEX BUFFER /////////////////////////////
////CREATE NEW INSTANCE OF IB WHEN NEEDED TO BIND NEW DATA TO PIPELINE ////
///////////////////////////////////////////////////////////////////////////

#include <windows.h>     //Window Library - Access to window functions
#include <d3d11_1.h>     //Core DX11 Library - Access DX11 Functions
#include <d3dcompiler.h> //Compile Library - Compiler for DX11 Code

#include <directxmath.h> //DX11 Math Library 
#include <directxcolors.h>//Color Math Library


using namespace DirectX; //Use default DX11 Naming 

#include <vector>
#include "SimpleVertexStructure.h"

class VertexBuffer
{
public:
	//Used for object creation and binding to render pipeline.

	VertexBuffer(ID3D11Device* device, ID3D11DeviceContext* device_context, std::vector<SimpleVertex>&vertices, ID3D11Buffer* vertex_buffer) : _pVertexBuffer(vertex_buffer) , Vertex(vertices)
	{
		D3D11_BUFFER_DESC VertexBufferDescrption;
		ZeroMemory(&VertexBufferDescrption, sizeof(VertexBufferDescrption));

		VertexBufferDescrption.Usage = D3D11_USAGE_DEFAULT;
		VertexBufferDescrption.ByteWidth = sizeof(SimpleVertex) * Vertex.size();
		VertexBufferDescrption.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		VertexBufferDescrption.CPUAccessFlags = 0;


		//Specifies data being used - Used in the process of creating buffers , calls reference to relevant index struct (InitData variable equals TrianglePyramidIndex)
		D3D11_SUBRESOURCE_DATA VertexBufferData;
		ZeroMemory(&VertexBufferData, sizeof(VertexBufferData));
		VertexBufferData.pSysMem = Vertex.data();

		device->CreateBuffer(&VertexBufferDescrption, &VertexBufferData, &_pVertexBuffer);
	
		
		VBOffset = 0;
		VBStride = sizeof(SimpleVertex);
	
	}

	~VertexBuffer()
	{
		Cleanup();
	}
	
	void Cleanup()
	{
		delete(_pVertexBuffer);


	}
	ID3D11Buffer* GetVertexBuffer()
	{
		return _pVertexBuffer;
	}

	UINT GetStride()
	{

		return VBStride;

	}
	UINT GetOffSet()
	{

		return VBOffset;

	}

	

private:

	ID3D11Buffer* _pVertexBuffer;
	UINT VBStride;
	UINT VBOffset;
	std::vector<SimpleVertex>Vertex;
};