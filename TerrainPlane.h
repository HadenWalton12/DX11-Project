#pragma once
#include "ObjectComponent.h"
#include "SimpleVertexStructure.h"
class TerrainPlane : public GameObjects
{
public:
	TerrainPlane(GraphicComponent* gfx, ShaderComponent* _Shader, TextureComponent* _Tex, XMFLOAT4X4 world) : GameObjects(gfx) {}
	void LoadMesh()
	{
		GeneratePlane(5, 5);
		SwitchDrawBuffers(VertexBuffer , IndexBuffer , _gfx);
	}
	void SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx) override;
	void GeneratePlane(int width, int depth);
	MeshData mesh;
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
};

