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
	//Terrain Loading Based from Frank Lunar Book
	MeshData LoadMesh()
	{
		//
		int column = 25;
		int row = 25;

		float width = 1.0f;
		float depth = 1.0f;

		UINT Vertex_Count = column * row;
		UINT Face_Count = (column - 1) * (row - 1) * 2 * 3;

		std::vector<SimpleVertex> TerrainVertex;
		std::vector <WORD> Indices;

		Indices.resize(Face_Count);
		TerrainVertex.resize(Vertex_Count);

		//Used in spacing calculations to determine the spacing between points
		float Half_Width = 0.5;
		float Half_Depth = 0.5;

		//Used to correctly space out the differences between each x and z value given.
			//Correctly maps out the grid to be square like. Called cell spacing
		float dx = width / (column - 1);
		float dz = depth / (row - 1);

		//Calculates the delta between each row and column of tex coords
		float du = 1.0f / (column - 1);
		float dv = 1.0f / (row - 1);


		for (UINT i = 0; i < row; i++)
		{
			//Updates Z/row value to be used to fill the next columns of data
			float z = Half_Depth - i * dz;

			//For each co
			for (UINT j = 0; j < column; j++)
			{
				//Increments value , update the next element column position
				float x = -Half_Width + j * dx;

				//Updates with current column instance , with the set value of the row
				TerrainVertex[i * column + j].Pos = XMFLOAT3(x, 0.0f, z);

				//As long as light positions are above this value(they will thats how lighting works) , lighting will work correctly , binding normals correctly
				TerrainVertex[i * column + j].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

				//Correctly maps texture bound to each vertex point
				TerrainVertex[i * column + j].TexC.x = j * dv;
				TerrainVertex[i * column + j].TexC.y = i * du;
			}
		}


		//Used as the element accesser , will modify overtime
		UINT k = 0;
		for (UINT i = 0; i < column - 1; ++i)
		{
			//Draws a Quad - Two Triangles
			for (UINT j = 0; j < row - 1; ++j)
			{
				//First Triangle in Quad
				///  
				Indices[k] = i * row + j;				//Access Initial Element Value
				Indices[k + 1] = i * row + j + 1;	   //Will access the next value from previous element 
				Indices[k + 2] = (i + 1) * row + j;    //Will access element on next row to create first triangle

				//Second Triangle in Quad
				Indices[k + 3] = (i + 1) * row + j;		//Will access the previous element to start draw of next triangle
				Indices[k + 5] = (i + 1) * row + j + 1; //Will access the next element from this previous value
				Indices[k + 4] = i * row + j + 1;		//Will access element value on row above previous two values to complete second triangle ,completing the Quad
			

				//To access elements for next Quad.
				k += 6; 
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
		_pTerrainTransform->SetTranslation(0.0f, -1.0f, 0.0f);
		_pTerrainTransform->SetScale(1000.0f, 1000.0f, 1000.0f);
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