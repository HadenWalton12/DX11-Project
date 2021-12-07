#include "TerrainPlane.h"

void TerrainPlane::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}

void TerrainPlane::GeneratePlane(int width , int depth)
{
	UINT Vertex_Count = width * depth;
	UINT Face_Count = (width - 1) * (depth - 1) * 2;

	SimpleVertex TerrainVertex[25];
	WORD Indices[175];


	float Half_Width = 0.5 * width;
	float Half_Depth = 0.5 * depth;

	float dx = width / (depth - 1); 
	float dz = depth / (width - 1);

	//Calculates the delta between each row and column of tex coords
	float du = 1.0f / (depth - 1);
	float dv = 1.0f / (width - 1);

	for (UINT i = 0; i < width; i++)
	{
		float z = Half_Depth - i * dz;

		for (UINT j = 0; j < depth ; j++)
		{

			float x = -Half_Width + j * dx;

			TerrainVertex[i * depth + j].Pos = XMFLOAT3(x, 0.0f, z);
			TerrainVertex[i * depth + j].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			TerrainVertex[i * depth + j].TexC.x = 0.0f;
			TerrainVertex[i * depth + j].TexC.y = 1.0f;
		}
	}

	//Grid Vertex  Buffer Description
	D3D11_BUFFER_DESC Gridbufferdescription;
	ZeroMemory(&Gridbufferdescription, sizeof(Gridbufferdescription));

	Gridbufferdescription.Usage = D3D11_USAGE_DEFAULT;
	Gridbufferdescription.ByteWidth = sizeof(SimpleVertex) * 25;
	Gridbufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Gridbufferdescription.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA InitGridData;
	ZeroMemory(&InitGridData, sizeof(InitGridData));
	InitGridData.pSysMem = TerrainVertex;

	_gfx->_pd3dDevice->CreateBuffer(&Gridbufferdescription, &InitGridData, &VertexBuffer);

	_mesh.VertexBuffer = VertexBuffer;
	_mesh.VBOffset = 0;
	_mesh.VBStride = sizeof(SimpleVertex);


	UINT k = 0;

	for (UINT i = 0; i < width - 1; i++)
	{
		for (UINT j = 0; j < depth - 1; j++)
		{
			Indices[k] = i * depth + j;
			Indices[k + 1] = i * depth + j + 1;
			Indices[k + 2] = (i + 1) * depth + j;

			Indices[k + 3] = (i + 1) * depth + j;
			Indices[k + 4] = i * depth + j + 1;
			Indices[k + 6] = (i + 1) * depth + j + 1;

			k += 6;



		}

	}


	//Cube Index Buffer Description
	D3D11_BUFFER_DESC GridIndexbufferdescription;
	ZeroMemory(&Gridbufferdescription, sizeof(GridIndexbufferdescription));

	GridIndexbufferdescription.Usage = D3D11_USAGE_DEFAULT;
	GridIndexbufferdescription.ByteWidth = sizeof(WORD) * 175;
	GridIndexbufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	GridIndexbufferdescription.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA GridCubeData;
	ZeroMemory(&GridCubeData, sizeof(GridCubeData));
	GridCubeData.pSysMem = Indices;
	_gfx->_pd3dDevice->CreateBuffer(&Gridbufferdescription, &InitGridData, &IndexBuffer);

	SwitchDrawBuffers(VertexBuffer, IndexBuffer, _gfx);


	



}
