#pragma once
#include "OBJLoader.h"
#include "GraphicComponent.h"


#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>
#include "DDSTextureLoader.h"
#include "SimpleVertexStructure.h"
#include "LightingValuesStructure.h"
#include "ConstantStructure.h"
#include "TimeStructure.h"
#include "MeshStructure.h"

class GameObjects
{
public:
	GameObjects(RenderingPipeline* pipeline);   //Constructor , when child class is called , we will need to initialise a gfx component and file , this is how we create our objects.Within we call OBJ load method , passing in our "_pd3dDevice" function , and "file" , so when we create child class
	//we can call the device pointer and the file name as a string to initialise the object loading , to which we call the draw the loaded mesh object
	~GameObjects();

	virtual void Update();
	virtual void Render();										//Draw method , to how we draw objects

private:



protected:
	
	std::vector<ID3D11ShaderResourceView*> _Textures;
	XMFLOAT4X4 world;

	MeshData LoadMesh(MeshData mesh, char* file, ID3D11Device* device)
	{
		mesh = OBJLoader::Load(file, device);
		return mesh;
	}

	MeshData LoadMesh(ID3D11Buffer* VB, UINT offset, UINT stride, ID3D11Buffer* IB, UINT index_count, MeshData mesh)
	{

		mesh.VertexBuffer = VB;
		mesh.VBOffset = offset;
		mesh.VBStride = stride;
		mesh.IndexBuffer = IB;
		mesh.IndexCount = index_count;

		return mesh;
	}

	
	//Hard Coded Objects
	IndexBuffer* _pIndexBuffer;
	VertexBuffer* _pVertexBuffer;

	//OBJ Objects 
	MeshData _mesh;


	virtual void CalculateTransformation();
	RenderingPipeline* _pPipeline;
	ID3D11Device* _pDevice;
	virtual void Initialise();

};

