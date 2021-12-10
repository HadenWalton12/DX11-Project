#include "TerrainPlane.h"

void TerrainPlane::CalculateTransformation()
{
	Timer t;
	XMMATRIX scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
	XMMATRIX translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x, ObjectRotation.y * t.time, ObjectRotation.z);


	XMStoreFloat4x4(&world, scale * translation * rotation);
}

void TerrainPlane::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
 	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}

MeshData TerrainPlane::GeneratePlane( ID3D11Device* device)
{
	int m = 8;
	int   n = 8;

	float width = 75.0f;
	float depth = 75.0f;

	UINT Vertex_Count = m * n;
	UINT Face_Count = (m - 1) * (n - 1) * 2;

	SimpleVertex TerrainVertex[100];
	WORD Indices[300];


	float Half_Width = 0.5 * width;
	float Half_Depth = 0.5 * depth;

	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	//Calculates the delta between each row and column of tex coords
	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	for (UINT i = 0; i < m; i++)
	{
		float z = Half_Depth - i * dz;

		for (UINT j = 0; j < n; j++)
		{

			float x = -Half_Width + j * dx;

			TerrainVertex[i * n + j].Pos = XMFLOAT3(x, 0.0f, z);
			TerrainVertex[i * n + j].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			TerrainVertex[i * n + j].TexC.x = j * du;
			TerrainVertex[i * n + j].TexC.y = i * dv;
		}
	}

	//Grid Vertex  Buffer Description
	D3D11_BUFFER_DESC Gridbufferdescription;
	ZeroMemory(&Gridbufferdescription, sizeof(Gridbufferdescription));

	Gridbufferdescription.Usage = D3D11_USAGE_DEFAULT;
	Gridbufferdescription.ByteWidth = sizeof(SimpleVertex) * 100;
	Gridbufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Gridbufferdescription.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA InitGridData;
	ZeroMemory(&InitGridData, sizeof(InitGridData));
	InitGridData.pSysMem = TerrainVertex;

	device->CreateBuffer(&Gridbufferdescription, &InitGridData, &VertexBuffer);




	UINT k = 0;

	for (UINT i = 0; i < m - 1; i++)
	{
		for (UINT j = 0; j < n - 1; j++)
		{
			Indices[k] = i * n + j;
			Indices[k + 1] = i * n + j + 1;
			Indices[k + 2] = (i + 1) * n + j;

			Indices[k + 3] = (i + 1) * n + j;
			Indices[k + 4] = i * n + j + 1;
			Indices[k + 5] = (i + 1) * n + j + 1;

			k += 6;



		}

	}


	//Cube Index Buffer Description
	D3D11_BUFFER_DESC TerrainIndexBufferDescription;
	ZeroMemory(&TerrainIndexBufferDescription, sizeof(TerrainIndexBufferDescription));

	TerrainIndexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	TerrainIndexBufferDescription.ByteWidth = sizeof(WORD) * 300;
	TerrainIndexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	TerrainIndexBufferDescription.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA IndexTerrainData;
	ZeroMemory(&IndexTerrainData, sizeof(IndexTerrainData));
	IndexTerrainData.pSysMem = Indices;
	device->CreateBuffer(&TerrainIndexBufferDescription, &IndexTerrainData, &IndexBuffer);

	_mesh.VertexBuffer = VertexBuffer;
	_mesh.VBOffset = 0;
	_mesh.VBStride = sizeof(SimpleVertex);
	_mesh.IndexBuffer = IndexBuffer;
	_mesh.IndexCount = 300;



	
	return _mesh;


}
