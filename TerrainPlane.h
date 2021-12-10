#pragma once
#include "ObjectComponent.h"
#include "SimpleVertexStructure.h"
class TerrainPlane : public GameObjects
{
public:
	TerrainPlane(GraphicComponent* gfx, ShaderComponent* _Shader, TextureComponent* _Tex, XMFLOAT4X4 world) : GameObjects(gfx) {}
	void LoadMesh() override
	{
	
		_mesh = GeneratePlane(_gfx->GetDevice());
		SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer, _gfx);
	}
	void CalculateTransformation()override;

	void SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx) override;
	MeshData GeneratePlane(  ID3D11Device* device);
	


	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
};

