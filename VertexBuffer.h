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
	//Used for object creation and binding to render pipeline.

	VertexBuffer(ID3D11Device* device, ID3D11DeviceContext* device_context, std::vector<SimpleVertex>& vertices, ID3D11Buffer* vertex_buffer)
	{
		ID3D11Buffer* vertex_buffer;

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

		device->CreateBuffer(&VertexBufferDescrption, &VertexBufferData, &vertex_buffer);
	}
};