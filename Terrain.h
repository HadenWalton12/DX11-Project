#pragma once
#include "DX.h"
#include "ObjectComponent.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "ObjectTranformation.h"
#include "EntityTransformation.h"
#include "TimeStructure.h"

class Terrain : public GameObjects
{
public:
	Terrain::Terrain(RenderCommands* render_command, TextureComponent* _Tex, DX* dx) : GameObjects(render_command)
	{
		_pDX11 = dx;
		_pRenderCommand = render_command;
		LoadMesh();
		_pTerrainTransform = new ObjectTranformation(&_TerrainWorld);

	}
	MeshData LoadMesh()
	{
		int m = 3;
		int n = 3;

		float width = 75.0f;
		float depth = 75.0f;

		UINT Vertex_Count = m * n;
		UINT Face_Count = (m - 1) * (n - 1) * 2;

		std::vector<SimpleVertex> TerrainVertex;
		std::vector <WORD> Indices;


		float Half_Width = 0.5 * width;
		float Half_Depth = 0.5 * depth;

		float dx = width / (n - 1);
		float dz = depth / (m - 1);

		//Calculates the delta between each row and column of tex coords
		float du = 1.0f / (n - 1);
		float dv = 1.0f / (m - 1);

		TerrainVertex.resize(Vertex_Count);

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
		//Resizes the indices vector to avoid calling the copy constructor for every new index
		Indices.resize(Face_Count * 3); // 3 indices per face

		// Iterate over each quad and compute indices.
		UINT k = 0;
		for (UINT i = 0; i < m - 1; ++i)
		{
			for (UINT j = 0; j < n - 1; ++j)
			{
				Indices[k] = i * n + j;
				Indices[k + 1] = i * n + j + 1;
				Indices[k + 2] = (i + 1) * n + j;

				Indices[k + 3] = (i + 1) * n + j;
				Indices[k + 4] = i * n + j + 1;
				Indices[k + 5] = (i + 1) * n + j + 1;

				k += 6; // next quad
			}
		}


		_pVertexBuffer = new VertexBuffer(_pRenderCommand->GetDevice(), _pRenderCommand->GetDeviceContext(), TerrainVertex, _VertexBuffer);
		_pIndexBuffer = new IndexBuffer(_pRenderCommand->GetDevice(), _pRenderCommand->GetDeviceContext(), Indices, _IndexBuffer);

		_mesh.VertexBuffer = _pVertexBuffer->GetVertexBuffer();
		_mesh.VBOffset = _pVertexBuffer->GetOffSet();
		_mesh.VBStride = _pVertexBuffer->GetStride();
		_mesh.IndexBuffer = _pIndexBuffer->GetIndexBuffer();
		_mesh.IndexCount = _pIndexBuffer->GetIndexCount();

		return _mesh;
	}
	void WorldTransformations() override
	{
		Timer t;
		_pTerrainTransform->SetTranslation(1.0f, -1.0f, 1.0f);
		_pTerrainTransform->SetScale(0.20f, 0.20f, 0.20f);
		t.Update();
		_pTerrainTransform->SetRotation(0.0f, 0.0f, 0.0f);
		_pTerrainTransform->CalculateWorldTransformation(_TerrainWorld);

		SetWorld(_pTerrainTransform->GetWorld());
	}

	void BindShaders() override
	{
		
			_pVertexShader = new VertexShader(_pRenderCommand->GetDevice(), _VS, _pRenderCommand->GetDeviceContext(), L"DX11 Framework.fx");
			_pPixelShader = new PixelShader(_pRenderCommand->GetDevice(), _PS, L"DX11 Framework.fx");
			_VS = _pVertexShader->GetShader();
			_PS = _pPixelShader->GetShader();
			_pRenderCommand->BindVertexShader(_VS);
			_pRenderCommand->BindPixelShader(_PS);
			_pRenderCommand->BindSampler(_pDX11->_pSamplerLinear);

	}
	Timer  t;


	XMFLOAT4X4 _TerrainWorld;
	ObjectTranformation* _pTerrainTransform;
	EntityTransformation transformation;
	ID3D11VertexShader* _VS;
	ID3D11PixelShader* _PS;
	ID3D11Buffer* _VertexBuffer;
	ID3D11Buffer* _IndexBuffer;

	VertexShader* _pVertexShader;
	VertexBuffer* _pVertexBuffer;
	IndexBuffer* _pIndexBuffer;

	DX* _pDX11;
	PixelShader* _pPixelShader;
	RenderCommands* _pRenderCommand;

};