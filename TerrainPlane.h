#pragma once
#include "ObjectComponent.h"
#include "SimpleVertexStructure.h"
class TerrainPlane : public GameObjects
{
public:
	TerrainPlane(GraphicComponent* gfx, ShaderComponent* _Shader, TextureComponent* _Tex, XMFLOAT4X4 world) : GameObjects(gfx, "") {}

	void GeneratePlane(int width, int depth);
	MeshData mesh;

};

